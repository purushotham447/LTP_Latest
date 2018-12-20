/*******************************************************************************
 * Copyright (c) 2016 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * This module implements the PortForward service proxy and the PortServer
 * proxy.
 * The PortForward service proxy allows accessing the PortForward service of
 * a remote peer from the current agent.
 * The PortServer service allows creating a local port to access a remote
 * port on the peer using the PortForward service proxy.
 */

#include <tcf/config.h>
#include <tcf/framework/mdep-threads.h>
#include <tcf/framework/errors.h>
#include <assert.h>
#include <tcf/framework/channel.h>
#include <tcf/framework/mdep-inet.h>
#include <tcf/framework/asyncreq.h>
#include <tcf/framework/trace.h>
#include <tcf/framework/myalloc.h>
#include <tcf/services/streamsservice.h>
#include <tcf/framework/json.h>
#include <tcf/framework/exceptions.h>
#include <tcf/framework/proxy.h>
#include <tcf/services/portforward_proxy.h>

#if ENABLE_PortForwardProxy || SERVICE_PortServer

#define OUT_BUF_SIZE            32*1024
#define IN_BUF_SIZE             32*1024

#define MAX_STREAM_WRITE        5       /* maximum number of parallel stream write commands */
#define MAX_STREAM_READ         5       /* maximum number of parallel stream read commands */


typedef void (*ConnectCallBack)(void * /* callback_data */, int /* error */, void * /* PortInfo */);
typedef void (*ReadCallBack)(void * /* callback_data */, int /* error */, char * /* buffer */, size_t /* read size */);
typedef void (*SendCallBack)(void * /* callback_data */, int /* error */);

struct PortServer {
    char id[256];
    LINK link;
    int sock;
    struct sockaddr * addr_buf;
    int addr_len;
    AsyncReqInfo accreq;
    int accept_in_progress;
    u_short local_port;
    int is_udp;               /* local port is UDP */
    Channel *   channel;
    PortAttribute * attrs;
    struct PortConnection * list;
    uint64_t port_index;
    int auto_connect;           /* automatically connect to port; don't wait */
                                /* for a client connection. */
    uint64_t auto_connect_period;    /* connection retry delay */
    PortConnectCallback connect_callback;         /* connect hook */
    PortDisconnectCallback disconnect_callback;   /* disconnect hook */
    PortRecvCallback recv_callback;               /* receive hook */
    void * callback_data;
    struct sockaddr  client_addr;    /* client address for UDP port */
    socklen_t client_addr_len;    /* client address for UDP port */
};

typedef struct PortReadInfo {
    struct PortConnection * conn;
    int idx;
} PortReadInfo;

typedef struct PortConnection {
    struct PortConnection * next;
    int fd;
    AsyncReqInfo recv_req;
    AsyncReqInfo send_req;
    PortServer * server;
    char inbuf[IN_BUF_SIZE];
    int connected;
    int lock_cnt;
    ReplyHandlerInfo * pending;
    char * in_stream_id;
    char * out_stream_id;
    PortReadInfo read_info[MAX_STREAM_READ];
    char read_buffer[MAX_STREAM_READ][IN_BUF_SIZE];
    size_t read_buffer_size[MAX_STREAM_READ];
    int pending_read_request;
    int pending_write_request;
    int shutdown_in_progress;
    char id[256];
    int send_in_progress;       /* -1 = no send request in progress */
    int pending_send_req;
} PortConnection;

static LINK server_list = TCF_LIST_INIT(server_list);
#define link2server(A)  ((PortServer *)((char *)(A) - offsetof(PortServer, link)))
static uint64_t port_server_id = 0;
static const char * channel_lock_svr_msg = "Port Forwarding server lock";

/* forward declaration */

static void set_socket_options(int sock);
static PortServer * create_server(Channel * c, PortAttribute * attrs);
static void port_connection_close(PortConnection * conn);
static void port_server_shutdown(PortServer * server);
static void ini_portforwarding(void);
static void send_packet_callback(PortConnection * conn, int error);
static void connect_port_callback(PortConnection * conn, int error);
static void read_packet_callback(PortConnection * conn, int error, int idx, size_t size);
static void port_connection_open(PortServer * server, int fd);

static void port_unlock(PortConnection * conn) {
    assert(conn->lock_cnt > 0);
    conn->lock_cnt--;
}

static void port_lock(PortConnection * conn) {
    conn->lock_cnt++;
}

static void read_stream_done(Channel *c, void *client_data, int error) {
    PortConnection * conn = ((PortReadInfo *) client_data)->conn;
    int idx = ((PortReadInfo *) client_data)->idx;

    size_t read_size = 0;

    conn->pending_read_request &= ~(1 << idx);
    if (error) {
        trace(LOG_ALWAYS, "Reply error %d: %s\n", error, errno_to_str(error));
        read_packet_callback(conn, error, idx, 0);
    }
    else {
        int end;
        InputStream *inp = &conn->server->channel->inp;
        int ch = peek_stream(inp);
        if (ch == 'n') {
            (void) read_stream(inp);
            if (read_stream(inp) != 'u') goto err_json_syntax;
            if (read_stream(inp) != 'l') goto err_json_syntax;
            if (read_stream(inp) != 'l') goto err_json_syntax;
        }
        else {
            JsonReadBinaryState state;

            json_read_binary_start(&state, inp);

            for (;;) {
                size_t rd = json_read_binary_data(&state,
                        conn->read_buffer[idx] + read_size,
                        sizeof conn->read_buffer[idx]);
                if (rd == 0) break;
                read_size += rd;
            }

            assert(state.size_start <= 0 || read_size == state.size_start);

            json_read_binary_end(&state);
        }
        json_test_char(&c->inp, MARKER_EOA);
        error = read_errno(inp);
        (void)json_read_long(inp);
        if (read_stream(inp) != 0) goto err_json_syntax;
        end = json_read_boolean(inp);
        json_test_char(&c->inp, MARKER_EOA);
        json_test_char(&c->inp, MARKER_EOM);

#if 0
        if (read_stream(inp) != 0 || read_stream(inp) != MARKER_EOM) goto err_json_syntax;
#endif
        if (end) read_packet_callback(conn, 0, idx, 0);
        else read_packet_callback(conn, 0, idx, read_size);
    }
    return;
    err_json_syntax: return;
}

static void read_getconfig_struct(InputStream * inp, const char * name,
        void * x) {
    PortConnection * conn = (PortConnection *) x;

    if (strcmp(name, "InputStream") == 0) conn->in_stream_id =
            json_read_alloc_string(inp);
    else if (strcmp(name, "OutputStream") == 0) conn->out_stream_id =
            json_read_alloc_string(inp);
    else json_skip_object(inp);
}

static void getconfig_cb(Channel * c, void * x, int error) {
    Trap trap;
    PortConnection * conn = (PortConnection *)x;

    if (set_trap(&trap)) {
        if (!error) {
            error = read_errno(&c->inp);
            json_read_struct(&c->inp, read_getconfig_struct, (void *)conn);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    connect_port_callback(conn, error);
}

static void portcreate_cb(Channel * c, void * x, int error) {
    Trap trap;
    PortConnection * conn = (PortConnection *)x;

    if (set_trap(&trap)) {
        if (!error) {
            error = read_errno(&c->inp);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    if (error) {
        connect_port_callback(conn, error);
    } else {
        conn->pending = protocol_send_command(conn->server->channel, "PortForward",
                "getConfig", getconfig_cb, conn);
        json_write_string(&conn->server->channel->out, conn->id);
        write_stream(&conn->server->channel->out, MARKER_EOA);
        write_stream(&conn->server->channel->out, MARKER_EOM);
    }
}

static void delete_config_done(Channel *c, void *client_data, int error) {
    PortConnection * conn = (PortConnection *) client_data;
    Trap trap;

    if (set_trap(&trap)) {
        if (!error) {
            error = read_errno(&c->inp);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    loc_free(conn->out_stream_id);
    conn->out_stream_id = NULL;
    loc_free(conn->in_stream_id);
    conn->in_stream_id = NULL;
    port_unlock(conn);
    port_connection_close(conn);
}

static void write_stream_done(Channel *c, void *client_data, int error) {
    Trap trap;
    PortConnection * conn = (PortConnection *) client_data;;

    if (set_trap(&trap)) {
        if (!error) {
            error = read_errno(&c->inp);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    assert (conn->pending_write_request <= MAX_STREAM_WRITE && conn->pending_write_request > 0);
    if (conn->pending_write_request == MAX_STREAM_WRITE) {
        send_packet_callback(conn, error);
    }
    conn->pending_write_request--;
}

static int read_packet(PortConnection * conn, int idx) {
    assert (is_dispatch_thread());

    assert ((conn->pending_read_request & (1 << idx)) == 0);
    if (conn->pending_read_request & (1 << idx)) {
        errno = ERR_IS_RUNNING;
        return -1;
    }
    port_lock(conn);
    conn->pending_read_request |= (1 << idx);
    (void) protocol_send_command(conn->server->channel, "Streams", "read", read_stream_done,
            &conn->read_info[idx]);
    json_write_string(&conn->server->channel->out, conn->in_stream_id);
    write_stream(&conn->server->channel->out, 0);
    json_write_long(&conn->server->channel->out, sizeof conn->read_buffer[idx]);
    write_stream(&conn->server->channel->out, MARKER_EOA);
    write_stream(&conn->server->channel->out, MARKER_EOM);
    return 0;
}


static int send_packet(PortConnection * conn, char * buffer, size_t size) {
    JsonWriteBinaryState state;

    assert (is_dispatch_thread());
    assert (conn->pending_write_request < MAX_STREAM_WRITE);
    protocol_send_command(conn->server->channel, "Streams", "write", write_stream_done,
            conn);
    json_write_string(&conn->server->channel->out, conn->out_stream_id);
    write_stream(&conn->server->channel->out, 0);
    json_write_long(&conn->server->channel->out, size);
    write_stream(&conn->server->channel->out, MARKER_EOA);
    json_write_binary_start(&state, &conn->server->channel->out, size);
    json_write_binary_data(&state, buffer, size);
    json_write_binary_end(&state);
    write_stream(&conn->server->channel->out, MARKER_EOA);
    write_stream(&conn->server->channel->out, MARKER_EOM);
    conn->pending_write_request ++;
    if (conn->pending_write_request  == MAX_STREAM_WRITE) {
        return 0;
    }
    else {
        send_packet_callback(conn, 0);
    }
    return 0;
}

static void read_getcapabilities_struct(InputStream * inp, const char * name,
        void * x) {
    json_skip_object(inp);
}

static void getcapabilities_cb(Channel * c, void * x, int error) {
    Trap trap;
    PortConnection * conn = (PortConnection *)x;
    PortAttribute * attr = conn->server->attrs;
    OutputStream * out = &conn->server->channel->out;

    if (set_trap(&trap)) {
        if (!error) {
            error = read_errno(&c->inp);
            json_read_struct(&c->inp, read_getcapabilities_struct, (void *)conn);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    if (error) {
        connect_port_callback(conn, error);
    } else {
        conn->pending = protocol_send_command(conn->server->channel, "PortForward",
                "create", portcreate_cb, conn);
        write_stream(out, '{');
        json_write_string(out, "ID");
        write_stream(out, ':');
        json_write_string(out, conn->id);
        while (attr != NULL) {
            if (strncmp(attr->name, "AutoConnect", 11) != 0) {
                write_stream(out, ',');
                json_write_string(out, attr->name);
                write_stream(out, ':');
                write_string(out, attr->value);
            }
            attr = attr->next;
        }
        write_stream(out, '}');
        write_stream(out, MARKER_EOA);
        write_stream(out, MARKER_EOM);
    }
}

static void connect_port(PortConnection * conn) {
    assert(is_dispatch_thread());

    sprintf(conn->id, "%s@%" PRIu64, conn->server->id, conn->server->port_index++);
    port_lock(conn);
    conn->pending = protocol_send_command(conn->server->channel, "PortForward",
            "getCapabilities", getcapabilities_cb, conn);
    write_string(&conn->server->channel->out, "null");
    write_stream(&conn->server->channel->out, MARKER_EOA);
    write_stream(&conn->server->channel->out, MARKER_EOM);
}

static void disconnect_port(PortConnection * conn) {
    assert (is_dispatch_thread());
    conn->shutdown_in_progress = 1;
    port_lock(conn);
    protocol_send_command(conn->server->channel, "PortForward", "delete",
            delete_config_done, conn);
    json_write_string(&conn->server->channel->out, conn->id);
    write_stream(&conn->server->channel->out, MARKER_EOA);
    write_stream(&conn->server->channel->out, MARKER_EOM);
}

static void set_socket_options(int sock) {
    int snd_buf = OUT_BUF_SIZE;
    int rcv_buf = IN_BUF_SIZE;
    struct linger optval;
    int i = 1;

    /* set SO_LINGER & SO_REUSEADDR socket options so that it closes the
     * connections gracefully, when required to close. */

    optval.l_onoff = 1;
    optval.l_linger = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_LINGER, (void *) &optval,
            sizeof(optval)) != 0) {
        int error = errno;
        trace(LOG_ALWAYS, "Unable to set SO_LINGER socket option: %s",
                errno_to_str(error));
    };

#if !(defined(_WIN32) || defined(__CYGWIN__))
    {
        const int i = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &i, sizeof(i))
                < 0) {
            int error = errno;
            trace(LOG_ALWAYS, "Unable to set SO_REUSEADDR socket option: ",
                    errno_to_str(error));
        }
    }
#endif

    /* Set TCP_NODELAY socket option to optimize communication */

    i = 1;
    if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &i, sizeof(i))
            < 0) {
        int error = errno;
        trace(LOG_ALWAYS, "Can't set TCP_NODELAY option on a socket: %s",
                errno_to_str(error));
    }
    i = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &i, sizeof(i))
            < 0) {
        int error = errno;
        trace(LOG_ALWAYS, "Can't set SO_KEEPALIVE option on a socket: %s",
                errno_to_str(error));
    }

    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *) &snd_buf,
            sizeof(snd_buf)) < 0) {
        trace(LOG_ALWAYS, "setsockopt(SOL_SOCKET,SO_SNDBUF,%d) error: %s",
                snd_buf, errno_to_str(errno));
    }
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *) &rcv_buf,
            sizeof(rcv_buf)) < 0) {
        trace(LOG_ALWAYS, "setsockopt(SOL_SOCKET,SO_RCVBUF,%d) error: %s",
                rcv_buf, errno_to_str(errno));
    }
}

static void send_packet_callback(PortConnection * conn, int error) {
    assert(is_dispatch_thread());
    port_unlock(conn);
    if (error != 0) {
        port_connection_close(conn);
    }
    else {
        port_lock(conn);
        conn->recv_req.u.sio.sock = conn->fd;
        conn->recv_req.u.sio.addrlen = sizeof(conn->server->client_addr);
        async_req_post(&conn->recv_req);
    }
}

static void read_packet_callback(PortConnection * conn, int error, int idx,
        size_t size) {

    assert(is_dispatch_thread());
    port_unlock(conn);
    if (error != 0 || size == 0) {
        port_connection_close(conn);
    }
    else {
        conn->read_buffer_size[idx] = size;

        /* Call read hooks if any. Note that those hooks can modify the
         * content of the packets (remove characters). */
        if (conn->server->recv_callback) {
            conn->server->recv_callback(conn->server, conn->read_buffer[idx], &conn->read_buffer_size[idx], IN_BUF_SIZE, conn->server->callback_data);
        }

        /* If no client is connected or if the filter has removed all
         * the packet content, do not post a send request. */

        if (conn->fd != -1 && conn->read_buffer_size[idx] != 0) {
            /* If there is already a send progress in request; postpone the
             * current one until it is completed. */
            if (conn->send_in_progress != -1) {
               conn->pending_send_req |= 1 << idx;
               return;
            }
            port_lock(conn);
            conn->send_in_progress = idx;
            assert (conn->pending_send_req == 0);
            conn->send_req.u.sio.bufp = conn->read_buffer[idx];
            conn->send_req.u.sio.bufsz = conn->read_buffer_size[idx];
            conn->send_req.u.sio.sock = conn->fd;
            conn->send_req.u.sio.addr = &conn->server->client_addr;
            conn->send_req.u.sio.addrlen = conn->server->client_addr_len;
            async_req_post(&conn->send_req);
        }
        else {
            read_packet(conn, idx);
        }
    }
}

static void port_connection_open_event(void * arg) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;

    while (qp != qhp) {
        PortServer * server = link2server(qp);
        if (server == (PortServer *)arg) {
            port_connection_open(server, server->is_udp ? server->sock : -1);
        }
        qp = qp->next;
    }
}

static int port_connection_bind(PortConnection * conn, int fd) {
    assert (conn->fd == -1);
    port_lock(conn);
    conn->fd = fd;
    conn->recv_req.u.sio.sock = conn->fd;
    conn->send_in_progress = -1;
    conn->pending_send_req = 0;
    conn->recv_req.u.sio.addrlen = sizeof(conn->server->client_addr);
    conn->recv_req.u.sio.addr = &conn->server->client_addr;
    async_req_post(&conn->recv_req);
    return 0;
}

static int port_connection_unbind(PortConnection * conn) {
    /* In UDP mode, connection and server are sharing the same
     * socket; do not close it when we close the connection, it
     * will be closed when the server is closed. */
    if (conn->fd != -1 && conn->server->is_udp == 0) {
        shutdown(conn->fd, SHUT_RDWR);
        closesocket(conn->fd);
    }
    conn->fd = -1;
    return 0;
}

static void connect_port_callback(PortConnection * conn, int error) {
    assert(is_dispatch_thread());
    port_unlock(conn);
    if (conn->shutdown_in_progress) return;
    if (error != 0) {
        port_connection_close(conn);
        return;
    }
    else {
        int idx;
        if (conn->server->connect_callback) conn->server->connect_callback(conn->server, conn->server->callback_data);
        conn->connected = 1;
        if (conn->fd != -1) {
            port_lock(conn);
            conn->recv_req.u.sio.sock = conn->fd;
            conn->recv_req.u.sio.addr = &conn->server->client_addr;
            conn->recv_req.u.sio.addrlen = sizeof(conn->server->client_addr);
            async_req_post(&conn->recv_req);
        }
        /* Send multiple TCF streams read requests in parallel; this is
         * to limit the performance impact on network with high latency. */
        for (idx = 0; idx < MAX_STREAM_READ; idx++)
            read_packet(conn, idx);
    }
}

static void done_recv_request(void * args) {
    AsyncReqInfo * req = (AsyncReqInfo *) args;
    PortConnection * conn = (PortConnection *) (req)->client_data;

    port_unlock(conn);
    if (conn->connected == 0) {
        port_connection_close(conn);
        return;
    }
    if (req->u.sio.rval == 0
            || (req->u.sio.rval == -1 && req->error != EINTR)) {
        /* Check if we are in auto connect mode and server has not been
         * shutdown */
        if (conn->server->auto_connect && conn->server->sock != -1) {
            /* Client has disconnected; don't close the connection if we
             * are in auto connect mode but simply unbind the client from
             * the port. */
            port_connection_unbind(conn);
        }
        else port_connection_close(conn);
        return;
    }
    port_lock(conn);
    conn->server->client_addr_len = req->u.sio.addrlen;
    send_packet(conn, (char *)req->u.sio.bufp, req->u.sio.rval);
}

static void done_send_request(void * args) {
    AsyncReqInfo * req = (AsyncReqInfo *) args;
    PortConnection * conn = (PortConnection *) (req)->client_data;
    int idx = conn->send_in_progress;

    port_unlock(conn);
    conn->send_in_progress = -1;
    if (conn->connected == 0) {
        port_connection_close(conn);
        return;
    }
    if (req->u.sio.rval == 0
           || (req->u.sio.rval == -1 && req->error != EINTR)) {
        /* Check if we are in auto connect mode and server has not been
         * shutdown
         */
        if (conn->server->auto_connect && conn->server->sock != -1) {
            /* Client has disconnected; don't close the connection if we
             * are in auto connect mode but simply unbind the client from
             * the port. */
            port_connection_unbind(conn);

            /* Still read packets from the target even if no client is
             * connected. This may have to be revisited. */
            read_packet(conn, idx);
        }
        else port_connection_close(conn);
        return;
    }

    if (conn->pending_send_req != 0) {
        int next_idx;
        int loop;

        /* Get the next packet to send. In general, it is the next buffer
         * but there are some error cases (connection lost, empty packet
         * received from TCF agent) which may break this rule. */
        for (loop = 0; loop < MAX_STREAM_READ; loop++) {
            next_idx = (idx + loop) % MAX_STREAM_READ;
            if (conn->pending_send_req & (1 << next_idx))
                break;
        }
        assert (loop != MAX_STREAM_READ &&
                        (conn->pending_send_req & (1 << next_idx)));


        conn->send_in_progress = next_idx;
        conn->pending_send_req &= ~(1 << next_idx);
        conn->send_req.u.sio.bufp = conn->read_buffer[next_idx];
        conn->send_req.u.sio.bufsz = conn->read_buffer_size[next_idx];
        port_lock(conn);
        conn->send_req.u.sio.sock = conn->fd;
        conn->send_req.u.sio.addr = &conn->server->client_addr;
        conn->send_req.u.sio.addrlen = conn->server->client_addr_len;
        async_req_post(&conn->send_req);
    }
    read_packet(conn, idx);
}

static void port_connection_close(PortConnection * conn) {
    PortServer * server = conn->server;
    PortConnection * prev;

    port_connection_unbind(conn);
    if (conn->connected) {
        if (server->disconnect_callback) server->disconnect_callback(server, server->callback_data);
        disconnect_port(conn);
        conn->connected = 0;
        return;
    }

    if (conn->lock_cnt > 0) return;
    if (server->list == conn) server->list = conn->next;
    else {
        prev = server->list;
        while (prev->next != conn)
            prev = prev->next;
        assert (prev->next == conn);
        prev->next = conn->next;
    }
    loc_free(conn);

    /* If the last port connection has been closed and server shutdown is
     * in progress, complete it.
     */
    if (server->list == NULL) {
        if (server->sock == -1) {
            port_server_shutdown(server);
        }
        else if (server->auto_connect) {
            /* Retry target connection */
            post_event_with_delay(port_connection_open_event, server, server->auto_connect_period * 1000000);
        }
    }
}

static void port_connection_open(PortServer * server, int fd) {
    PortConnection * conn;

    if (server->channel == NULL || is_channel_closed(server->channel)) {
        closesocket(fd);
        return;
    }

    conn = (PortConnection *)loc_alloc_zero(sizeof(PortConnection));

    if (conn == NULL) {
        closesocket(fd);
    }
    else {
        int idx = 0;
        conn->recv_req.client_data = conn;
        conn->recv_req.done = done_recv_request;
        conn->recv_req.type = server->is_udp ? AsyncReqRecvFrom : AsyncReqRecv;
        conn->recv_req.u.sio.sock = fd;
        conn->recv_req.u.sio.flags = 0;
        conn->recv_req.u.sio.bufp = conn->inbuf;
        conn->recv_req.u.sio.bufsz = IN_BUF_SIZE;
        conn->recv_req.u.sio.addr = &server->client_addr;
        conn->recv_req.u.sio.addrlen = sizeof(conn->server->client_addr);

        conn->send_req.client_data = conn;
        conn->send_req.done = done_send_request;
        conn->send_req.type = server->is_udp ? AsyncReqSendTo : AsyncReqSend;
        conn->send_req.u.sio.sock = fd;
        conn->send_req.u.sio.flags = 0;

        conn->send_in_progress = -1;    /* no send request in progress */
        for (idx = 0; idx < MAX_STREAM_READ; idx++) {
            conn->read_info[idx].idx = idx;
            conn->read_info[idx].conn = conn;
        }

        conn->fd = fd;
        conn->server = server;
        conn->next = server->list;
        server->list = conn;

        connect_port(conn);
    }
}

static void port_server_accept_done(void * x) {
    AsyncReqInfo * req = (AsyncReqInfo *) x;
    PortServer * server = (PortServer *) req->client_data;

    if (server->sock < 0 || req->error) {
        /* Server closed or fatal error */
        if (server->sock >= 0 && req->error) {
            trace(LOG_ALWAYS, "Port Server accept failed for server %s: %s", server->id, errno_to_str(req->error));
        }
        server->accept_in_progress = 0;
        port_server_shutdown(server);
        return;
    }
    else {
        int fd = req->u.acc.rval;
        set_socket_options(fd); /* set socket options */
        trace (LOG_ALWAYS, "Accept done on server for server %s", server->id);

        /* In auto connect mode, we accept only a single client for the
         * port.
         */
        if (server->auto_connect == 0) {
            port_connection_open(server, fd);
        } else if (server->list == NULL || !server->list->connected || server->list->fd != -1) {
            closesocket(fd);
        } else {
            port_connection_bind(server->list, fd);
        }
    }
    server->accreq.u.acc.addrlen = server->addr_len;
    async_req_post(req);
}

static void free_port_redirection_attrs(PortAttribute * attrs) {
    while (attrs != NULL) {
        PortAttribute * attr = attrs;
        attrs = attr->next;
        loc_free(attr->name);
        loc_free(attr->value);
        loc_free(attr);
    }
}

static void port_server_shutdown(PortServer * server) {
    PortConnection * conn;

    /* It seems we need to use shutdown to unblock threads blocked on recv/send */
    if (server->sock != -1) {
        shutdown(server->sock, SHUT_RDWR);
        if (closesocket(server->sock) == -1) perror("closesocket");
        server->sock = -1;
        list_remove(&server->link);
        /* Closing socket is enough; the various port connections
         * will be deleted when server deletion will be detected. In this
         * case this API will be called again. */
        return;
    }

    for (conn = server->list; conn != NULL; ) {
        PortConnection * next_conn;
        next_conn = conn->next;
        port_connection_close(conn);
        conn = next_conn;
    }


    if (server->list != NULL) return;    /* Wait for all port connections to be closed */
    if (server->accept_in_progress) return;        /* Wait for accept request to be aborted */

    channel_unlock_with_msg(server->channel, channel_lock_svr_msg);
    free_port_redirection_attrs(server->attrs);
    loc_free(server->addr_buf);
    loc_free(server);
}

static PortServer * create_server(Channel * c, PortAttribute * attrs) {
    int sock = -1;
    struct sockaddr_in addr;
    PortAttribute * attr = attrs;
#if defined(_WRS_KERNEL)
    int addrlen;
#else
    socklen_t addrlen;
#endif
    u_short port_number;
    PortServer * server = NULL;
    int is_udp = 0;           /* do we use a server UDP -or TCP- port? */
    char * port_config = NULL;
    int error = 0;
    int auto_connect = 0;
    uint64_t auto_connect_period = 0;
    unsigned int local_port = 0;

    while (attr != NULL) {
        if (strcmp(attr->name,  "Port") == 0) {
            ByteArrayInputStream buf;
            InputStream * inp = create_byte_array_input_stream(&buf, attr->value, strlen(attr->value));
            port_config = json_read_alloc_string(inp);
            if (strncasecmp(port_config, "udp:", strlen("udp:")) == 0) {
                is_udp = 1;
            }
        }
        else if (strcmp(attr->name, "AutoConnect") == 0) {
            ByteArrayInputStream buf;
            InputStream * inp = create_byte_array_input_stream(&buf, attr->value, strlen(attr->value));
            auto_connect = json_read_boolean(inp);
        }
        else if (strcmp(attr->name, "AutoConnectPeriod") == 0) {
            ByteArrayInputStream buf;
            InputStream * inp = create_byte_array_input_stream(&buf, attr->value, strlen(attr->value));
            auto_connect_period = json_read_ulong(inp);
        }
        else if (strcmp(attr->name, "LocalPort") == 0) {
            ByteArrayInputStream buf;
            InputStream * inp = create_byte_array_input_stream(&buf, attr->value, strlen(attr->value));
            local_port = (unsigned int) json_read_uint64(inp);
        }
        attr = attr->next;
    }
    if (port_config == NULL) {
        error = set_errno(ERR_OTHER, "No port configuration is specified");
    }
    if (error == 0) {
        loc_free(port_config);
        memset((void *) &addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = (u_short) htons(local_port);

        if (is_udp) sock = socket(AF_INET, SOCK_DGRAM, 0);
        else if ((sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0) set_socket_options(sock); /* set socket options */

        if (sock == -1) error = errno;
    }

    if (error == 0) {
        if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            error = errno;
        }
    }

    if (error == 0 && !is_udp) {
        if (listen(sock, 16) != 0) error = errno;
    }

    if (error == 0) {
        /* Get port property in case the default port could not be used or
         * the client specified a port that the system converts to a
         * dynamic port number. */
        addrlen = sizeof addr;
        if (getsockname(sock, (struct sockaddr *) &addr, &addrlen) < 0) error = errno;
    }

    if (error == 0) {
        port_number = (u_short) ntohs(addr.sin_port);

        server = (PortServer *)loc_alloc_zero(sizeof(PortServer));
        server->sock = sock;
        server->is_udp = is_udp;
#if defined(SOCK_MAXADDRLEN)
        server->addr_len = SOCK_MAXADDRLEN;
#else
        server->addr_len = 0x1000;
#endif
        server->addr_buf = (struct sockaddr *)loc_alloc(server->addr_len);
        server->local_port = port_number;

        if (!server->is_udp) {
            server->accept_in_progress = 1;
            server->auto_connect = auto_connect;

            server->accreq.done = port_server_accept_done;
            server->accreq.client_data = server;
            server->accreq.type = AsyncReqAccept;
            server->accreq.u.acc.sock = sock;
            server->accreq.u.acc.addr = server->addr_buf;
            server->accreq.u.acc.addrlen = server->addr_len;
            async_req_post(&server->accreq);
            }
        else
            {
            /* For UDP, automatically connect to the port since there is no
             * connection request we can detect.
             */
            server->auto_connect = 1;
            }
        server->auto_connect_period = auto_connect_period;

        list_add_last(&server->link, &server_list);
        channel_lock_with_msg(server->channel = c, channel_lock_svr_msg);
        snprintf (server->id, sizeof(server->id), "PS%" PRIu64, port_server_id++);
        server->attrs = attrs;
    }
    if (error == 0) return server;
    else {
        if (sock != -1) closesocket(sock);
        loc_free(server);
        return NULL ;
    }
}

static void event_channel_closed(Channel * c) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;

    while (qp != qhp) {
        PortServer * server = link2server(qp);
        qp = qp->next;
        if (server->channel == c) {
            port_server_shutdown(server);
        }
    }
}

int destroy_port_server(PortServer * server) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;
    while (qp != qhp) {
        if (server == (PortServer *)link2server(qp)) break;
        qp = qp->next;
    }
    if (qp == qp->next) {
        errno = EINVAL;
        return -1;
    }
    port_server_shutdown(server);
    return 0;
}

PortServer * create_port_server(Channel * c, PortAttribute * attrs, PortConnectCallback connect_callback, PortDisconnectCallback disconnect_callback, PortRecvCallback recv_callback, void * callback_data) {
    PortServer * server;
    assert (c != NULL);
    assert (attrs != NULL);

    if (c == NULL || attrs == NULL) {
        free_port_redirection_attrs(attrs);
        errno = EINVAL;
        return NULL;
    }
    ini_portforwarding();
    server = create_server(c, attrs);
    if (server == NULL) {
        free_port_redirection_attrs(attrs);
        return NULL;
    }
    else {
        server->connect_callback = connect_callback;
        server->disconnect_callback = disconnect_callback;
        server->recv_callback = recv_callback;
        server->callback_data = callback_data;
        if (server->auto_connect) {
            /* If auto connect mode is set, immediately try to connect to the
             * port.  */
            if (server->auto_connect_period == 0) server->auto_connect_period = 3;
            port_connection_open(server, server->is_udp ? server->sock : -1);
        }
        return server;
    }
}

int get_port_server_info(PortServer * server, PortServerInfo * info) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;
    while (qp != qhp) {
        if (server == (PortServer *)link2server(qp)) break;
        qp = qp->next;
    }
    if (qp == qp->next) {
        errno = EINVAL;
        return -1;
    }
    info->is_udp = server->is_udp;
    info->port = server->local_port;
    return 0;
}

static void ini_portforwarding() {
    static int ini_port_forward = 0;

    if (ini_port_forward == 0) {
        add_channel_close_listener(event_channel_closed);
        ini_port_forward = 1;
    }
}

#if SERVICE_PortServer
static PortServer * find_port_server(const char * id) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;
    while (qp != qhp) {
        PortServer * server = link2server(qp);
        if (strcmp(server->id, id) == 0) return server;
        qp = qp->next;
    }
    return NULL;
}

static void write_port_server_info(OutputStream * out, PortServer * server) {
    PortAttribute * attr = server->attrs;
    write_stream(out, '{');
    json_write_string(out, "ID");
    write_stream(out, ':');
    json_write_string(out, server->id);
    write_stream(out, ',');
    json_write_string(out, "AutoConnect");
    write_stream(out, ':');
    json_write_boolean(out, server->auto_connect);
    write_stream(out, ',');
    if (server->is_udp) json_write_string(out, "UdpPort");
    else json_write_string(out, "TcpPort");
    write_stream(out, ':');
    json_write_ulong(out, server->local_port);
    while (attr != NULL) {
        if (strcmp(attr->name, "AutoConnect") != 0) {
            write_stream(out, ',');
            json_write_string(out, attr->name);
            write_stream(out, ':');
            write_string(out, attr->value);
        }
        attr = attr->next;
    }
    write_stream(out, '}');
}

static void read_port_server_property(InputStream * inp, const char * name,
        void * args) {
    PortAttribute ** attrs = (PortAttribute **) args;
    PortAttribute * attr = (PortAttribute *)loc_alloc_zero(sizeof(PortAttribute));
    attr->value = json_read_object(inp);
    attr->name = loc_strdup(name);
    attr->next = *attrs;
    *attrs = attr;
}

static void port_server_cmd_create(char * token, Channel * c) {
    int err = 0;
    PortAttribute * attrs = NULL;
    PortServer * server;
    Channel * port_channel;
    json_read_struct(&c->inp, read_port_server_property, &attrs);
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    /* In case the current channel is a proxy (value-add), use the
     * target channel. Otherwise, use the provided channel. */
    port_channel = proxy_get_target_channel(c);
    if (port_channel == NULL) port_channel = c;
    server = create_port_server(c, attrs, NULL, NULL, NULL, NULL);
    if (server == NULL) err = errno;
    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_errno(&c->out, err);
    if (err) write_stringz(&c->out, "null");
    else {
        write_port_server_info(&c->out, server);
        write_stream(&c->out, 0);
    }
    write_stream(&c->out, MARKER_EOM);
}

static void port_server_cmd_delete(char * token, Channel * c) {
    char id[256];
    int err = 0;
    PortServer * server;

    json_read_string(&c->inp, id, sizeof(id));
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    if ((server = find_port_server(id)) == NULL) err = EINVAL;
    else port_server_shutdown(server);
    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_errno(&c->out, err);
    write_stream(&c->out, MARKER_EOM);
}

static void port_server_cmd_get_capabilities(char * token, Channel * c) {
    OutputStream * out = &c->out;
    int err = 0;
    char * id;

    id = json_read_alloc_string(&c->inp);
    json_test_char(&c->inp, MARKER_EOA);
    json_test_char(&c->inp, MARKER_EOM);
    loc_free(id);

    write_stringz(out, "R");
    write_stringz(out, token);
    write_errno(out, err);
    if (err) {
        write_stringz(&c->out, "null");
    }
    else {
        write_stream(out, '{');
        write_stream(out, '}');
        write_stream(out, 0);
    }
    write_stream(out, MARKER_EOM);
}

static void port_server_cmd_list(char * token, Channel * c) {
    LINK * qhp = &server_list;
    LINK * qp = qhp->next;
    int cnt = 0;
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);
    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_errno(&c->out, 0);
    write_stream(&c->out, '[');
    while (qp != qhp) {
        PortServer * server = link2server(qp);
        if (cnt > 0) write_stream(&c->out, ',');
        json_write_string(&c->out, server->id);
        qp = qp->next;
        cnt++;
    }
    write_stream(&c->out, ']');
    write_stream(&c->out, 0);
    write_stream(&c->out, MARKER_EOM);
}

static void port_server_cmd_get_config(char * token, Channel * c) {
    char id[256];
    PortServer * server;
    int err = 0;
    json_read_string(&c->inp, id, sizeof(id));
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);
    if ((server = find_port_server(id)) == NULL) err = EINVAL;
    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_errno(&c->out, err);
    if (err == 0) {
        write_port_server_info(&c->out, server);
        write_stream(&c->out, 0);
    }
    else {
        write_stringz(&c->out, "null");
    }
    write_stream(&c->out, MARKER_EOM);
}

void ini_port_server_service(const char * name_ext, Protocol * proto, TCFBroadcastGroup * bcg) {
    char * service_name = (char *)loc_alloc(strlen("PortServer") + (name_ext == NULL ? 1 : strlen(name_ext) + 1));
    sprintf(service_name, "PortServer%s", name_ext == NULL ? "" : name_ext);
    add_command_handler(proto, service_name, "getConfig", port_server_cmd_get_config);
    add_command_handler(proto, service_name, "create", port_server_cmd_create);
    add_command_handler(proto, service_name, "list", port_server_cmd_list);
    add_command_handler(proto, service_name, "delete", port_server_cmd_delete);
    add_command_handler(proto, service_name, "getCapabilities", port_server_cmd_get_capabilities);
}
#endif
#endif
