/*******************************************************************************
 * Copyright (c) 2007, 2016 Wind River Systems, Inc. and others.
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
 * This module forwards handling of process/thread OS contexts to remote peer.
 */

#include <tcf/config.h>

#if ENABLE_DebugContext && ENABLE_ContextProxy

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <tcf/framework/mdep-fs.h>
#include <tcf/framework/context.h>
#include <tcf/framework/myalloc.h>
#include <tcf/framework/trace.h>
#include <tcf/framework/exceptions.h>
#include <tcf/framework/protocol.h>
#include <tcf/framework/json.h>
#include <tcf/framework/cache.h>
#include <tcf/services/symbols.h>
#include <tcf/services/pathmap.h>
#include <tcf/services/memorymap.h>
#include <tcf/services/stacktrace.h>
#include <tcf/services/linenumbers.h>
#include <tcf/services/context-proxy.h>
#if ENABLE_ContextMux
#include <tcf/framework/context-mux.h>
#endif


typedef struct ContextCache ContextCache;
typedef struct MemoryCache MemoryCache;
typedef struct StackFrameCache StackFrameCache;
typedef struct PeerCache PeerCache;
typedef struct RegisterProps RegisterProps;
typedef struct RegisterCache RegisterCache;
#if ENABLE_ContextISA
typedef struct DefIsaCache DefIsaCache;
#endif
typedef struct ErrorAddress ErrorAddress;

#define CTX_ID_HASH_SIZE 101

struct ContextCache {
    char id[256];
    char parent_id[256];
    char process_id[256];
    char creator_id[256];
    char symbols_id[256];
    char rc_group_id[256];
    char bp_group_id[256];
    char cpu_id[256];
    char * file;
    char * name;
    int  big_endian;
    Context * ctx;
    PeerCache * peer;
    LINK id_hash_link;

    /* Memory Map */
    MemoryMap client_map;
    MemoryMap target_map;
    AbstractCache mmap_cache;
    ErrorReport * mmap_error;
    ReplyHandlerInfo * pending_get_mmap;
    int mmap_is_valid;
    int has_mmap;

    /* Register definitions */
    AbstractCache regs_cache;
    ErrorReport * reg_error;
    unsigned reg_max;
    unsigned reg_size;
    RegisterProps * reg_props;
    RegisterDefinition * reg_defs;
    RegisterDefinition * pc_def;
    int pending_regs_cnt;
    int regs_done;

    /* Run Control Properties */
    int has_state;
    int is_container;
    int can_suspend;
    long can_resume;
    int can_terminate;
    int can_detach;
    unsigned word_size;
#if ENABLE_ContextExtraProperties
    char ** props_names;
    char ** props_values;
    unsigned props_cnt;
    unsigned props_max;
#endif

    /* Run Control State */
    int intercepted;
    int pc_valid;
    uint64_t suspend_pc;
    char * suspend_reason;
    char * signal_name;
    char ** bp_ids;

    /* Memory */
    LINK mem_cache_list;

    /* Stack trace */
    LINK stk_cache_list;

#if ENABLE_ContextISA
    /* Default Isa cache */
    DefIsaCache * def_isa_cache;
#endif
};

struct RegisterProps {
    RegisterDefinition def;
    char * id;
};

struct RegisterData {
    uint8_t * data;
    uint8_t * mask;
};

struct RegisterCache {
    ErrorReport * error;
    int valid;
};

struct ErrorAddress {
    ContextAddress addr;
    ContextAddress size;
    long stat;
};

struct MemoryCache {
    LINK link_ctx;
    ContextCache * ctx;
    AbstractCache cache;
    ErrorReport * error;
    ErrorAddress * errors_address;
    unsigned errors_address_cnt;
    ContextAddress addr;
    void * buf;
    size_t size;
    ReplyHandlerInfo * pending;
    int disposed;
};

struct StackFrameCache {
    LINK link_ctx;
    ContextCache * ctx;
    AbstractCache cache;
    ErrorReport * error;
    ContextAddress ip;
    ContextAddress rp;
    StackFrame info;
    RegisterCache * reg_cache;
    RegisterData reg_data;
    RegisterDefinition ** reg_defs;
    unsigned reg_pending;
    unsigned reg_cnt;
    int reg_valid;
    ReplyHandlerInfo * pending;
    int disposed;
};

struct PeerCache {
    LINK link_all;
    LINK context_id_hash[CTX_ID_HASH_SIZE];
    Channel * host;
    Channel * target;
    ForwardingInputStream bck_buf;
    ForwardingInputStream fwd_buf;
    InputStream * bck_inp;
    InputStream * fwd_inp;

    /* Initial Run Control context tree retrieval */
    int rc_done;
    int rc_pending_cnt;
    ErrorReport * rc_error;
    AbstractCache rc_cache;
};

#if ENABLE_ContextISA
struct DefIsaCache {
    ContextCache * ctx;
    AbstractCache cache;
    ErrorReport * error;
    ContextAddress addr;
    int isa_valid;
    char * def_isa;
    ContextAddress max_instruction_size;
    ContextAddress alignment;
    ReplyHandlerInfo * pending;
    int disposed;
};
#endif

typedef struct MMListener {
    MemoryMapEventListener * listener;
    void * args;
} MMListener;

#define peers2peer(A)    ((PeerCache *)((char *)(A) - offsetof(PeerCache, link_all)))
#define ctx2mem(A)       ((MemoryCache *)((char *)(A) - offsetof(MemoryCache, link_ctx)))
#define ctx2stk(A)       ((StackFrameCache *)((char *)(A) - offsetof(StackFrameCache, link_ctx)))
#define idhashl2ctx(A)   ((ContextCache *)((char *)(A) - offsetof(ContextCache, id_hash_link)))

static LINK peers = TCF_LIST_INIT(peers);

static MemoryRegion * mem_buf = NULL;
static unsigned mem_buf_max = 0;
static unsigned mem_buf_pos = 0;

static unsigned * ids_buf = NULL;
static unsigned ids_buf_max = 0;
static unsigned ids_buf_pos = 0;

static char * str_buf = NULL;
static unsigned str_buf_max = 0;
static unsigned str_buf_pos = 0;

static MMListener * mm_listeners = NULL;
static unsigned mm_listener_cnt = 0;
static unsigned mm_listener_max = 0;

static size_t context_extension_offset = 0;

#define EXT(ctx) ((ContextCache **)((char *)(ctx) + context_extension_offset))

static const char CONTEXT_PROXY[] = "ContextProxy";
static const char RUN_CONTROL[] = "RunControl";
static const char MEMORY_MAP[] = "MemoryMap";
static const char PATH_MAP[] = "PathMap";
static const char MEMORY[] = "Memory";
static const char REGISTERS[] = "Registers";

#if ENABLE_ContextMux
/*
 * When Context Multiplexer is enabled, all context APIs must be defined even for proxy context
 */
const char * context_suspend_reason(Context * ctx) {
    return NULL ;
}

int context_stop(Context * ctx) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_continue(Context * ctx) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_resume(Context * ctx, int mode, ContextAddress range_start, ContextAddress range_end) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_can_resume(Context * ctx, int mode) {
    ContextCache * c = *EXT(ctx);
    if (mode == RM_TERMINATE) return c->can_terminate;
    if (mode == RM_DETACH) return c->can_detach;
    return c->can_resume & (1 << mode);
}

int context_single_step(Context * ctx) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_get_canonical_addr(Context * ctx, ContextAddress addr, Context ** canonical_ctx,
        ContextAddress * canonical_addr, ContextAddress * block_addr, ContextAddress * block_size) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_get_supported_bp_access_types(Context * ctx) {
    return 0;
}
int context_plant_breakpoint(ContextBreakpoint * bp) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_unplant_breakpoint(ContextBreakpoint * bp) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

uint8_t * get_break_instruction(Context * ctx, size_t * size) {
    return NULL ;
}
#endif

static unsigned hash_ctx_id(const char * id) {
    int i;
    unsigned h = 0;
    for (i = 0; id[i]; i++) h += id[i];
    return h % CTX_ID_HASH_SIZE;
}

static ContextCache * find_context_cache(PeerCache * p, const char * id) {
    LINK * h = p->context_id_hash + hash_ctx_id(id);
    LINK * l = h->next;
    while (l != h) {
        ContextCache * c = idhashl2ctx(l);
        if (!c->ctx->exited && strcmp(c->id, id) == 0) return c;
        l = l->next;
    }
    return NULL;
}

static void set_context_links(ContextCache * c) {
    assert(c->peer->rc_done);
    loc_free(c->ctx->name);
    c->ctx->big_endian = c->big_endian;
    c->ctx->name = c->name ? loc_strdup(c->name) : NULL;
    if (c->parent_id[0] && c->ctx->parent == NULL) {
        ContextCache * h = find_context_cache(c->peer, c->parent_id);
        if (h != NULL) {
            (c->ctx->parent = h->ctx)->ref_count++;
            list_add_last(&c->ctx->cldl, &h->ctx->children);
        }
        else {
            trace(LOG_ALWAYS, "Invalid parent ID: %s", c->parent_id);
        }
    }
    if (c->process_id[0]) {
        ContextCache * h = find_context_cache(c->peer, c->process_id);
        if (h != NULL) {
            c->ctx->mem = h->ctx;
            c->ctx->mem_access = c == h ? MEM_ACCESS_INSTRUCTION | MEM_ACCESS_DATA : 0;
        }
        else {
            trace(LOG_ALWAYS, "Invalid process ID: %s", c->process_id);
        }
    }
    else {
        c->ctx->mem_access = 0;
        c->ctx->mem = NULL;
    }
    if (c->creator_id[0] && c->ctx->creator == NULL) {
        ContextCache * h = find_context_cache(c->peer, c->creator_id);
        if (h != NULL) {
            (c->ctx->creator = h->ctx)->ref_count++;
        }
        else {
            trace(LOG_ALWAYS, "Invalid creator ID: %s", c->creator_id);
        }
    }
}

static void add_context_cache(PeerCache * p, ContextCache * c) {
    LINK * h = p->context_id_hash + hash_ctx_id(c->id);
    c->peer = p;
    c->ctx = create_context(c->id);
    c->ctx->ref_count = 1;
    c->ctx->stopped = 1;
    *EXT(c->ctx) = c;
    list_init(&c->mem_cache_list);
    list_init(&c->stk_cache_list);
    list_add_first(&c->id_hash_link, h);
    list_add_first(&c->ctx->ctxl, &context_root);
    if (p->rc_done) set_context_links(c);
    send_context_created_event(c->ctx);
}

static void free_memory_cache(MemoryCache * m) {
    list_remove(&m->link_ctx);
    m->disposed = 1;
    if (m->pending == NULL) {
        release_error_report(m->error);
        cache_dispose(&m->cache);
        loc_free(m->errors_address);
        loc_free(m->buf);
        loc_free(m);
    }
}

#if ENABLE_ContextISA
static void free_isa_cache(DefIsaCache * i) {
    i->disposed = 1;
    if (i->pending == NULL) {
        release_error_report(i->error);
        cache_dispose(&i->cache);
        if (i->def_isa != NULL) loc_free(i->def_isa);
        loc_free(i);
    }
}
#endif

static void free_stack_frame_cache(StackFrameCache * s) {
    list_remove(&s->link_ctx);
    s->disposed = 1;
    if (s->pending == NULL) {
        release_error_report(s->error);
        cache_dispose(&s->cache);
        if (s->reg_cache != NULL) {
            unsigned i;
            assert(s->info.is_top_frame);
            for (i = 0; i < s->ctx->reg_max; i++) {
                release_error_report(s->reg_cache[i].error);
            }
            loc_free(s->reg_cache);
        }
        if (s->info.area != NULL) {
            loc_free(s->info.area->directory);
            loc_free(s->info.area->file);
            loc_free(s->info.area);
        }
        loc_free(s->info.func_id);
        loc_free(s->reg_data.data);
        loc_free(s->reg_data.mask);
        loc_free(s->reg_defs);
        loc_free(s);
    }
}

static void free_context_extra_props(ContextCache * c) {
#if ENABLE_ContextExtraProperties
    unsigned i;
    for (i = 0; i < c->props_cnt; i++) {
        loc_free(c->props_names[i]);
        loc_free(c->props_values[i]);
    }
    loc_free(c->props_names);
    loc_free(c->props_values);
#endif
}

static void free_context_cache(ContextCache * c) {
    assert(c->pending_get_mmap == NULL);
    assert(c->pending_regs_cnt == 0);
    cache_dispose(&c->mmap_cache);
    cache_dispose(&c->regs_cache);
    release_error_report(c->mmap_error);
    release_error_report(c->reg_error);
    loc_free(c->file);
    loc_free(c->name);
    context_clear_memory_map(&c->target_map);
    loc_free(c->target_map.regions);
    loc_free(c->reg_defs);
    loc_free(c->suspend_reason);
    loc_free(c->signal_name);
    loc_free(c->bp_ids);
    if (c->reg_props != NULL) {
        unsigned i;
        for (i = 0; i < c->reg_max; i++) {
            loc_free(c->reg_props[i].id);
            loc_free(c->reg_props[i].def.role);
            loc_free(c->reg_props[i].def.name);
        }
        loc_free(c->reg_props);
    }
    assert(list_is_empty(&c->id_hash_link));
    if (!list_is_empty(&c->mem_cache_list)) {
        LINK * l = c->mem_cache_list.next;
        while (l != &c->mem_cache_list) {
            MemoryCache * m = ctx2mem(c->mem_cache_list.next);
            l = l->next;
            free_memory_cache(m);
        }
    }
    if (!list_is_empty(&c->stk_cache_list)) {
        LINK * l = c->stk_cache_list.next;
        while (l != &c->stk_cache_list) {
            StackFrameCache * s = ctx2stk(c->stk_cache_list.next);
            l = l->next;
            free_stack_frame_cache(s);
        }
    }
#if ENABLE_ContextISA
    if (c->def_isa_cache != NULL) free_isa_cache(c->def_isa_cache);
#endif
    free_context_extra_props(c);
    loc_free(c);
}

static void clear_context_cache(ContextCache * c) {
    LINK * l;

    if (c->peer->rc_done) {
        LINK * x = context_root.next;
        while (x != &context_root) {
            Context * ctx = ctxl2ctxp(x);
            if (ctx->mem == c->ctx->mem) {
                ContextCache * p = *EXT(ctx);
                l = p->mem_cache_list.next;
                while (l != &p->mem_cache_list) {
                    MemoryCache * m = ctx2mem(p->mem_cache_list.next);
                    l = l->next;
                    if (!m->pending) free_memory_cache(m);
                }
            }
            x = x->next;
        }
    }

    l = c->stk_cache_list.next;
    while (l != &c->stk_cache_list) {
        StackFrameCache * f = ctx2stk(c->stk_cache_list.next);
        l = l->next;
        free_stack_frame_cache(f);
    }
}

static void read_run_control_context_property(InputStream * inp, const char * name, void * args) {
    ContextCache * ctx = (ContextCache *)args;
    if (strcmp(name, "ID") == 0) json_read_string(inp, ctx->id, sizeof(ctx->id));
    else if (strcmp(name, "ParentID") == 0) json_read_string(inp, ctx->parent_id, sizeof(ctx->parent_id));
    else if (strcmp(name, "ProcessID") == 0) json_read_string(inp, ctx->process_id, sizeof(ctx->process_id));
    else if (strcmp(name, "CreatorID") == 0) json_read_string(inp, ctx->creator_id, sizeof(ctx->creator_id));
    else if (strcmp(name, "SymbolsGroup") == 0) json_read_string(inp, ctx->symbols_id, sizeof(ctx->symbols_id));
    else if (strcmp(name, "RCGroup") == 0) json_read_string(inp, ctx->rc_group_id, sizeof(ctx->rc_group_id));
    else if (strcmp(name, "BPGroup") == 0) json_read_string(inp, ctx->bp_group_id, sizeof(ctx->bp_group_id));
    else if (strcmp(name, "CPUGroup") == 0) json_read_string(inp, ctx->cpu_id, sizeof(ctx->cpu_id));
    else if (strcmp(name, "File") == 0) ctx->file = json_read_alloc_string(inp);
    else if (strcmp(name, "Name") == 0) ctx->name = json_read_alloc_string(inp);
    else if (strcmp(name, "HasState") == 0) ctx->has_state = json_read_boolean(inp);
    else if (strcmp(name, "IsContainer") == 0) ctx->is_container = json_read_boolean(inp);
    else if (strcmp(name, "WordSize") == 0) ctx->word_size = json_read_long(inp);
    else if (strcmp(name, "CanSuspend") == 0) ctx->can_suspend = json_read_boolean(inp);
    else if (strcmp(name, "CanResume") == 0) ctx->can_resume = json_read_long(inp);
    else if (strcmp(name, "CanTerminate") == 0) ctx->can_terminate = json_read_boolean(inp);
    else if (strcmp(name, "CanDetach") == 0) ctx->can_detach = json_read_boolean(inp);
    else if (strcmp(name, "BigEndian") == 0) ctx->big_endian = json_read_boolean(inp);
    else {
#if ENABLE_ContextExtraProperties
        if (ctx->props_cnt >= ctx->props_max) {
            ctx->props_max += 16;
            ctx->props_names = (char **)loc_realloc(ctx->props_names, sizeof(char *) * ctx->props_max);
            ctx->props_values = (char **)loc_realloc(ctx->props_values, sizeof(char *) * ctx->props_max);
        }
        ctx->props_names[ctx->props_cnt] = loc_strdup(name);
        ctx->props_values[ctx->props_cnt] = json_read_object(inp);
        ctx->props_cnt++;
#else
        json_skip_object(inp);
#endif
    }
}

static void read_context_suspended_data(InputStream * inp, const char * name, void * args) {
    ContextCache * ctx = (ContextCache *)args;
    if (strcmp(name, "Signal") == 0 && ctx->ctx != NULL) ctx->ctx->signal = json_read_long(inp);
    else if (strcmp(name, "SignalName") == 0) ctx->signal_name = json_read_alloc_string(inp);
    else if (strcmp(name, "BPs") == 0) ctx->bp_ids = json_read_alloc_string_array(inp, NULL);
    else json_skip_object(inp);
}

static void clear_context_suspended_data(ContextCache * ctx) {
    loc_free(ctx->suspend_reason);
    loc_free(ctx->signal_name);
    loc_free(ctx->bp_ids);
    if (ctx->ctx != NULL) ctx->ctx->signal = 0;
    ctx->pc_valid = 0;
    ctx->suspend_pc = 0;
    ctx->suspend_reason = NULL;
    ctx->signal_name = NULL;
    ctx->bp_ids = NULL;
}

static void clear_memory_map_data(ContextCache * ctx) {
    context_clear_memory_map(&ctx->target_map);
    release_error_report(ctx->mmap_error);
    ctx->mmap_is_valid = 0;
    ctx->mmap_error = NULL;
    if (ctx->has_mmap) {
        memory_map_event_mapping_changed(ctx->ctx);
        ctx->has_mmap = 0;
    }
}

static void read_context_added_item(InputStream * inp, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = (ContextCache *)loc_alloc_zero(sizeof(ContextCache));

    json_read_struct(inp, read_run_control_context_property, c);

    if (find_context_cache(p, c->id) == NULL &&
        (c->parent_id[0] == 0 || find_context_cache(p, c->parent_id) != NULL)) {
        add_context_cache(p, c);
    }
    else {
        if (p->rc_done) trace(LOG_ALWAYS, "Invalid ID in 'context added' event: %s", c->id);
        free_context_cache(c);
    }
}

static void read_context_changed_item(InputStream * inp, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = NULL;
    ContextCache * b = (ContextCache *)loc_alloc_zero(sizeof(ContextCache));
    json_read_struct(inp, read_run_control_context_property, b);
    c = find_context_cache(p, b->id);
    if (c != NULL) {
        strcpy(c->parent_id, b->parent_id);
        strcpy(c->process_id, b->process_id);
        strcpy(c->creator_id, b->creator_id);
        strcpy(c->symbols_id, b->symbols_id);
        strcpy(c->rc_group_id, b->rc_group_id);
        strcpy(c->bp_group_id, b->bp_group_id);
        strcpy(c->cpu_id, b->cpu_id);
        loc_free(c->file);
        c->file = b->file;
        b->file = NULL;
        loc_free(c->name);
        c->name = b->name;
        b->name = NULL;
        c->has_state = b->has_state;
        c->is_container = b->is_container;
        c->can_suspend = b->can_suspend;
        c->can_resume = b->can_resume;
        c->can_terminate = b->can_terminate;
        c->can_detach = b->can_detach;
        c->big_endian = b->big_endian;
#if ENABLE_ContextExtraProperties
        free_context_extra_props(c);
        c->props_cnt = b->props_cnt;
        c->props_max = b->props_max;
        c->props_names = b->props_names;
        c->props_values = b->props_values;
        b->props_names = NULL;
        b->props_values = NULL;
        b->props_cnt = 0;
#endif
        if (p->rc_done) set_context_links(c);
        send_context_changed_event(c->ctx);
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'context changed' event: %s", b->id);
    }
    free_context_cache(b);
}

static void read_context_removed_item(InputStream * inp, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = NULL;
    char id[256];
    json_read_string(inp, id, sizeof(id));
    c = find_context_cache(p, id);
    if (c != NULL) {
        assert(*EXT(c->ctx) == c);
        send_context_exited_event(c->ctx);
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'context removed' event: %s", id);
    }
}

static void read_container_suspended_item(InputStream * inp, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = NULL;
    char id[256];
    json_read_string(inp, id, sizeof(id));
    c = find_context_cache(p, id);
    if (c != NULL) {
        assert(*EXT(c->ctx) == c);
        if (!c->intercepted) {
            c->intercepted = 1;
            clear_context_cache(c);
        }
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'container suspended' event: %s", id);
    }
}

static void read_container_resumed_item(InputStream * inp, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = NULL;
    char id[256];
    json_read_string(inp, id, sizeof(id));
    c = find_context_cache(p, id);
    if (c != NULL) {
        assert(*EXT(c->ctx) == c);
        if (c->intercepted) {
            c->intercepted = 0;
            clear_context_suspended_data(c);
        }
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'container resumed' event: %s", id);
    }
}

static void event_context_added(Channel * c, void * args) {
    PeerCache * p = (PeerCache *)args;
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "contextAdded");
    json_read_array(p->bck_inp, read_context_added_item, p);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);
}

static void event_context_changed(Channel * c, void * args) {
    PeerCache * p = (PeerCache *)args;
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "contextChanged");
    json_read_array(p->bck_inp, read_context_changed_item, p);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);
}

static void event_context_removed(Channel * c, void * args) {
    PeerCache * p = (PeerCache *)args;
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "contextRemoved");
    json_read_array(p->bck_inp, read_context_removed_item, p);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);
}

static void event_context_suspended(Channel * ch, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache buf;
    ContextCache * c = &buf;

    assert(p->target == ch);
    memset(&buf, 0, sizeof(buf));
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "contextSuspended");
    json_read_string(p->bck_inp, c->id, sizeof(c->id));
    json_test_char(p->bck_inp, MARKER_EOA);
    c = find_context_cache(p, c->id);
    if (c == NULL) c = &buf;
    else clear_context_suspended_data(c);
    c->suspend_pc = json_read_uint64(p->bck_inp);
    json_test_char(p->bck_inp, MARKER_EOA);
    c->suspend_reason = json_read_alloc_string(p->bck_inp);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_read_struct(p->bck_inp, read_context_suspended_data, c);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);

    if (c != &buf) {
        assert(*EXT(c->ctx) == c);
        c->pc_valid = 1;
        if (!c->intercepted) {
            c->intercepted = 1;
            clear_context_cache(c);
        }
    }
    else {
        if (p->rc_done) trace(LOG_ALWAYS, "Invalid ID in 'context suspended' event: %s", c->id);
        clear_context_suspended_data(c);
    }
}

static void event_context_resumed(Channel * ch, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache * c = NULL;
    char id[256];

    assert(p->target == ch);
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "contextResumed");
    json_read_string(p->bck_inp, id, sizeof(id));
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);

    c = find_context_cache(p, id);
    if (c != NULL) {
        assert(*EXT(c->ctx) == c);
        if (c->intercepted) {
            c->intercepted = 0;
            clear_context_suspended_data(c);
        }
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'context resumed' event: %s", id);
    }
}

static void event_container_suspended(Channel * ch, void * args) {
    PeerCache * p = (PeerCache *)args;
    ContextCache buf;
    ContextCache * c = &buf;

    assert(p->target == ch);
    memset(&buf, 0, sizeof(buf));
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "containerSuspended");
    json_read_string(p->bck_inp, c->id, sizeof(c->id));
    json_test_char(p->bck_inp, MARKER_EOA);
    c = find_context_cache(p, c->id);
    if (c == NULL) c = &buf;
    else clear_context_suspended_data(c);
    c->suspend_pc = json_read_uint64(p->bck_inp);
    json_test_char(p->bck_inp, MARKER_EOA);
    c->suspend_reason = json_read_alloc_string(p->bck_inp);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_read_struct(p->bck_inp, read_context_suspended_data, c);
    json_test_char(p->bck_inp, MARKER_EOA);
    if (c != &buf) {
        assert(*EXT(c->ctx) == c);
        c->pc_valid = 1;
        if (!c->intercepted) {
            c->intercepted = 1;
            clear_context_cache(c);
        }
    }
    else {
        if (p->rc_done) trace(LOG_ALWAYS, "Invalid ID in 'container suspended' event: %s", c->id);
        clear_context_suspended_data(c);
    }
    json_read_array(p->bck_inp, read_container_suspended_item, p);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);
}

static void event_container_resumed(Channel * c, void * args) {
    PeerCache * p = (PeerCache *)args;
    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, RUN_CONTROL);
    write_stringz(&p->host->out, "containerResumed");
    json_read_array(p->bck_inp, read_container_resumed_item, p);
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);
}

static void event_register_changed(Channel * channel, void * args) {
    char id[256];
    PeerCache * peer = (PeerCache *)args;

    write_stringz(&peer->host->out, "E");
    write_stringz(&peer->host->out, REGISTERS);
    write_stringz(&peer->host->out, "registerChanged");
    json_read_string(peer->bck_inp, id, sizeof(id));
    json_test_char(peer->bck_inp, MARKER_EOA);
    json_test_char(peer->bck_inp, MARKER_EOM);

    if (peer->rc_done) {
        ContextCache * c = NULL;
        const char * ctx_id = NULL;
        int frame = STACK_TOP_FRAME;
        unsigned reg_num = 0;

        id2reg_num(id, &ctx_id, &frame, &reg_num);
        if (ctx_id != NULL) c = find_context_cache(peer, ctx_id);

        if (c != NULL) {
            while (!list_is_empty(&c->stk_cache_list)) {
                free_stack_frame_cache(ctx2stk(c->stk_cache_list.next));
            }
        }
    }
}

static void read_memory_changed_struct(InputStream * inp, const char * name, void * args) {
    ErrorAddress * addr = (ErrorAddress *)args;
    if (strcmp(name, "addr") == 0) addr->addr = (ContextAddress)json_read_uint64(inp);
    else if (strcmp(name, "size") == 0) addr->size = (ContextAddress)json_read_uint64(inp);
    else json_skip_object(inp);
}

static void read_memory_changed_item(InputStream * inp, void * args) {
    ContextCache * c = (ContextCache *)args;
    ErrorAddress addr;
    memset(&addr, 0, sizeof(ErrorAddress));
    if (json_read_struct(inp, read_memory_changed_struct, &addr) && addr.size > 0 && c != NULL) {
        LINK * x = context_root.next;
        assert(*EXT(c->ctx) == c);
        while (x != &context_root) {
            Context * ctx = ctxl2ctxp(x);
            if (ctx->mem == c->ctx->mem) {
                ContextCache * ctx_cache = *EXT(ctx);
                LINK * l = ctx_cache->mem_cache_list.next;
                while (l != &ctx_cache->mem_cache_list) {
                    MemoryCache * m = ctx2mem(ctx_cache->mem_cache_list.next);
                    l = l->next;
                    if (m->addr + m->size >= m->addr && m->addr + m->size <= addr.addr) continue;
                    if (addr.addr + addr.size > addr.addr && addr.addr + addr.size <= m->addr) continue;
                    free_memory_cache(m);
                }
            }
            x = x->next;
        }
    }
}

static void event_memory_changed(Channel * channel, void * args) {
    char id[256];
    PeerCache * peer = (PeerCache *)args;
    ContextCache * c = NULL;

    write_stringz(&peer->host->out, "E");
    write_stringz(&peer->host->out, MEMORY);
    write_stringz(&peer->host->out, "memoryChanged");
    json_read_string(peer->bck_inp, id, sizeof(id));
    json_test_char(peer->bck_inp, MARKER_EOA);
    if (peer->rc_done) {
        c = find_context_cache(peer, id);
        if (c == NULL) trace(LOG_ALWAYS, "Invalid ID in 'memory changed' event: %s", id);
    }
    json_read_array(peer->bck_inp, read_memory_changed_item, c);
    json_test_char(peer->bck_inp, MARKER_EOA);
    json_test_char(peer->bck_inp, MARKER_EOM);
}

static void event_memory_map_changed(Channel * c, void * args) {
    char id[256];
    PeerCache * p = (PeerCache *)args;
    ContextCache * ctx = NULL;

    write_stringz(&p->host->out, "E");
    write_stringz(&p->host->out, MEMORY_MAP);
    write_stringz(&p->host->out, "changed");
    json_read_string(p->bck_inp, id, sizeof(id));
    json_test_char(p->bck_inp, MARKER_EOA);
    json_test_char(p->bck_inp, MARKER_EOM);

    ctx = find_context_cache(p, id);
    if (ctx != NULL) {
        assert(*EXT(ctx->ctx) == ctx);
        clear_memory_map_data(ctx);
    }
    else if (p->rc_done) {
        trace(LOG_ALWAYS, "Invalid ID in 'memory map changed' event: %s", id);
    }
}

static void command_path_map_set(char * token, Channel * c, void * args) {
    PeerCache * p = (PeerCache *)args;
    write_stringz(&p->target->out, "C");
    write_stream(&p->target->out, 'R');
    write_stringz(&p->target->out, token);
    write_stringz(&p->target->out, PATH_MAP);
    write_stringz(&p->target->out, "set");
    set_path_map(p->host, p->fwd_inp);
    json_test_char(p->fwd_inp, MARKER_EOA);
    json_test_char(p->fwd_inp, MARKER_EOM);
}

static void validate_peer_cache_children(Channel * c, void * args, int error);

void create_context_proxy(Channel * host, Channel * target, int forward_pm) {
    int i;
    LINK * l;
    PeerCache * p;
    for (l = peers.next; l != &peers; l = l->next) {
        p = peers2peer(l);
        if (p->target == target) return;
    }
    p = (PeerCache *)loc_alloc_zero(sizeof(PeerCache));
    p->host = host;
    p->target = target;
    p->bck_inp = create_forwarding_input_stream(&p->bck_buf, &target->inp, &host->out);
    p->fwd_inp = create_forwarding_input_stream(&p->fwd_buf, &host->inp, &target->out);
    for (i = 0; i < CTX_ID_HASH_SIZE; i++) list_init(p->context_id_hash + i);
    list_add_first(&p->link_all, &peers);
    channel_lock(host);
    channel_lock(target);
    add_event_handler2(target, RUN_CONTROL, "contextAdded", event_context_added, p);
    add_event_handler2(target, RUN_CONTROL, "contextChanged", event_context_changed, p);
    add_event_handler2(target, RUN_CONTROL, "contextRemoved", event_context_removed, p);
    add_event_handler2(target, RUN_CONTROL, "contextSuspended", event_context_suspended, p);
    add_event_handler2(target, RUN_CONTROL, "contextResumed", event_context_resumed, p);
    add_event_handler2(target, RUN_CONTROL, "containerSuspended", event_container_suspended, p);
    add_event_handler2(target, RUN_CONTROL, "containerResumed", event_container_resumed, p);
    add_event_handler2(target, MEMORY_MAP, "changed", event_memory_map_changed, p);
    add_event_handler2(target, MEMORY, "memoryChanged", event_memory_changed, p);
    add_event_handler2(target, REGISTERS, "registerChanged", event_register_changed, p);
    if (forward_pm) add_command_handler2(host->protocol, PATH_MAP, "set", command_path_map_set, p);
    /* Retrieve initial set of run control contexts */
    protocol_send_command(p->target, RUN_CONTROL, "getChildren", validate_peer_cache_children, p);
    write_stringz(&p->target->out, "null");
    write_stream(&p->target->out, MARKER_EOM);
    p->rc_pending_cnt++;
}

static void validate_peer_cache_context(Channel * c, void * args, int error);
static void validate_peer_cache_state(Channel * c, void * args, int error);

static void read_rc_children_item(InputStream * inp, void * args) {
    char id[256];
    PeerCache * p = (PeerCache *)args;

    json_read_string(inp, id, sizeof(id));

    if (find_context_cache(p, id) == NULL) {
        ContextCache * c = (ContextCache *)loc_alloc_zero(sizeof(ContextCache));
        strcpy(c->id, id);
        c->peer = p;
        protocol_send_command(p->target, RUN_CONTROL, "getContext", validate_peer_cache_context, c);
        json_write_string(&p->target->out, c->id);
        write_stream(&p->target->out, 0);
        write_stream(&p->target->out, MARKER_EOM);
        p->rc_pending_cnt++;
    }
}

static void set_rc_done(PeerCache * p) {
    if (p->rc_pending_cnt == 0) {
        int i;
        LINK * l;
        p->rc_done = 1;
        for (i = 0; i < CTX_ID_HASH_SIZE; i++) {
            LINK * h = p->context_id_hash + i;
            for (l = h->next; l != h; l = l->next) {
                set_context_links(idhashl2ctx(l));
            }
        }
        cache_notify(&p->rc_cache);
    }
}

static void set_rc_error(PeerCache * p, int error) {
    if (error == 0) return;
    if (get_error_code(error) == ERR_INV_CONTEXT) return;
    if (get_error_code(error) == ERR_ALREADY_EXITED) return;
    if (p->rc_error != NULL) return;
    p->rc_error = get_error_report(error);
}

static void validate_peer_cache_children(Channel * c, void * args, int error) {
    PeerCache * p = (PeerCache *)args;
    Trap trap;

    assert(p->target == c);
    assert(p->rc_pending_cnt > 0);
    if (set_trap(&trap)) {
        p->rc_pending_cnt--;
        if (!error) {
            error = read_errno(&c->inp);
            json_read_array(&c->inp, read_rc_children_item, p);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    set_rc_error(p, error);
    set_rc_done(p);
}

static void validate_peer_cache_context(Channel * c, void * args, int error) {
    ContextCache * x = (ContextCache *)args;
    PeerCache * p = x->peer;
    Trap trap;

    assert(p->target == c);
    assert(p->rc_pending_cnt > 0);
    if (set_trap(&trap)) {
        p->rc_pending_cnt--;
        if (error) {
            set_rc_error(p, error);
            free_context_cache(x);
        }
        else {
            set_rc_error(p, error = read_errno(&c->inp));
            json_read_struct(&c->inp, read_run_control_context_property, x);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
            if (error || find_context_cache(p, x->id) != NULL) {
                free_context_cache(x);
            }
            else if (x->has_state) {
                protocol_send_command(p->target, RUN_CONTROL, "getState", validate_peer_cache_state, x);
                json_write_string(&p->target->out, x->id);
                write_stream(&p->target->out, 0);
                write_stream(&p->target->out, MARKER_EOM);
                p->rc_pending_cnt++;
            }
            else {
                add_context_cache(p, x);
                protocol_send_command(p->target, RUN_CONTROL, "getChildren", validate_peer_cache_children, p);
                json_write_string(&p->target->out, x->id);
                write_stream(&p->target->out, 0);
                write_stream(&p->target->out, MARKER_EOM);
                p->rc_pending_cnt++;
            }
        }
        clear_trap(&trap);
    }
    else {
        set_rc_error(p, trap.error);
        free_context_cache(x);
    }
    set_rc_done(p);
}

static void validate_peer_cache_state(Channel * c, void * args, int error) {
    ContextCache * x = (ContextCache *)args;
    PeerCache * p = x->peer;
    Trap trap;

    assert(p->target == c);
    assert(p->rc_pending_cnt > 0);
    if (set_trap(&trap)) {
        p->rc_pending_cnt--;
        if (error) {
            set_rc_error(p, error);
            free_context_cache(x);
        }
        else {
            set_rc_error(p, error = read_errno(&c->inp));
            clear_context_suspended_data(x);
            x->pc_valid = json_read_boolean(&c->inp);
            json_test_char(&c->inp, MARKER_EOA);
            x->suspend_pc = json_read_uint64(&c->inp);
            json_test_char(&c->inp, MARKER_EOA);
            x->suspend_reason = json_read_alloc_string(&c->inp);
            json_test_char(&c->inp, MARKER_EOA);
            json_read_struct(&c->inp, read_context_suspended_data, x);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);

            if (error || find_context_cache(p, x->id) != NULL) {
                free_context_cache(x);
            }
            else {
                add_context_cache(p, x);
                x->intercepted = x->pc_valid;
                if (x->intercepted) {
                    clear_context_cache(x);
                }
                protocol_send_command(p->target, RUN_CONTROL, "getChildren", validate_peer_cache_children, p);
                json_write_string(&p->target->out, x->id);
                write_stream(&p->target->out, 0);
                write_stream(&p->target->out, MARKER_EOM);
                p->rc_pending_cnt++;
            }
        }
        clear_trap(&trap);
    }
    else {
        set_rc_error(p, trap.error);
        free_context_cache(x);
    }
    set_rc_done(p);
}

Context * id2ctx(const char * id) {
    LINK * l;
    Channel * c = cache_channel();
    assert(c != NULL);
    for (l = peers.next; l != &peers; l = l->next) {
        PeerCache * p = peers2peer(l);
        if (p->host == c || p->target == c) {
            if (p->rc_pending_cnt > 0) {
                cache_wait(&p->rc_cache);
            }
            else if (p->rc_error != NULL) {
                set_error_report_errno(p->rc_error);
            }
            else if (!p->rc_done) {
                cache_wait(&p->rc_cache);
            }
            else {
                ContextCache * h = find_context_cache(p, id);
                return h ? h->ctx : NULL;
            }
        }
    }
    return NULL;
}

int context_has_state(Context * ctx) {
    return (*EXT(ctx))->has_state;
}

#if ENABLE_ContextExtraProperties
int context_get_extra_properties(Context * ctx, const char *** names, const char *** values, int * cnt) {
    ContextCache * c = *EXT(ctx);
    *names = (const char **)c->props_names;
    *values = (const char **)c->props_values;
    *cnt = (int)c->props_cnt;
    return 0;
}
#endif

Context * context_get_group(Context * ctx, int group) {
    ContextCache * c = *EXT(ctx);
    switch (group) {
    case CONTEXT_GROUP_SYMBOLS:
        if (c->symbols_id[0]) {
            ContextCache * h = find_context_cache(c->peer, c->symbols_id);
            if (h != NULL) return h->ctx;
        }
        break;
    case CONTEXT_GROUP_BREAKPOINT:
        if (c->bp_group_id[0]) {
            ContextCache * h = find_context_cache(c->peer, c->bp_group_id);
            if (h != NULL) return h->ctx;
        }
        return NULL;
    case CONTEXT_GROUP_INTERCEPT:
        if (c->rc_group_id[0]) {
            ContextCache * h = find_context_cache(c->peer, c->rc_group_id);
            if (h != NULL) return h->ctx;
        }
        return ctx;
    case CONTEXT_GROUP_CPU:
        if (c->cpu_id[0]) {
            ContextCache * h = find_context_cache(c->peer, c->cpu_id);
            if (h != NULL) return h->ctx;
        }
        return ctx;
    }
    return ctx->mem;
}

static void cb_check_memory_error_struct(InputStream * inp, const char * name, void * args) {
    ErrorAddress * error = (ErrorAddress *)args;

    if (strcmp(name, "addr") == 0) error->addr = json_read_int64(inp);
    else if (strcmp(name, "size") == 0) error->size = json_read_int64(inp);
    else if (strcmp(name, "stat") == 0) error->stat = json_read_long(inp);
    else json_skip_object(inp);
}

static void cb_check_memory_error_array(InputStream * inp, void * args) {
    MemoryCache * m = (MemoryCache *)args;
    m->errors_address_cnt++;
    m->errors_address = (ErrorAddress *)loc_realloc(m->errors_address,
            sizeof(ErrorAddress) * m->errors_address_cnt);
    memset(m->errors_address + m->errors_address_cnt - 1, 0, sizeof(ErrorAddress));
    json_read_struct(inp, cb_check_memory_error_struct,
            m->errors_address + m->errors_address_cnt - 1);
}

static void validate_memory_cache(Channel * c, void * args, int error) {
    MemoryCache * m = (MemoryCache *)args;
    Context * ctx = m->ctx->ctx;
    Trap trap;

    assert(m->pending != NULL);
    assert(m->error == NULL);
    assert(m->errors_address == NULL);
    if (set_trap(&trap)) {
        m->pending = NULL;
        if (!error) {
            size_t pos = 0;
            JsonReadBinaryState state;
            json_read_binary_start(&state, &c->inp);
            for (;;) {
                int rd = json_read_binary_data(&state, (int8_t *)m->buf + pos, m->size - pos);
                if (rd == 0) break;
                pos += rd;
            }
            json_read_binary_end(&state);
            json_test_char(&c->inp, MARKER_EOA);
            error = read_errno(&c->inp);
            json_read_array(&c->inp, cb_check_memory_error_array, m);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    m->error = get_error_report(error);
    cache_notify_later(&m->cache);
    if (m->disposed) free_memory_cache(m);
    context_unlock(ctx);
}

int context_read_mem(Context * ctx, ContextAddress address, void * buf, size_t size) {
    ContextCache * cache = *EXT(ctx);
    Channel * c = cache->peer->target;
    MemoryCache * m = NULL;
    LINK * l = NULL;
    Trap trap;

    if (!set_trap(&trap)) return -1;
    if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
    if (!cache->peer->rc_done) cache_wait(&cache->peer->rc_cache);

    for (l = cache->mem_cache_list.next; l != &cache->mem_cache_list; l = l->next) {
        m = ctx2mem(l);
        if (address >= m->addr && address + size <= m->addr + m->size) {
            int valid = 0;
            if (m->pending != NULL) cache_wait(&m->cache);
            memcpy(buf, (int8_t *)m->buf + (address - m->addr), size);
            if (m->error != NULL && m->errors_address_cnt > 0) {
                /* Check if the requested range is in a valid memory read */
                unsigned ix;
                for (ix = 0; ix < m->errors_address_cnt; ix++) {
                    ErrorAddress * err_addr = m->errors_address + ix;
                    if (err_addr->stat != 0) continue;
                    if (address >= err_addr->addr && address - err_addr->addr + size <= err_addr->size) {
                        valid = 1;
                        break;
                    }
                }
            }
            if (!valid) set_error_report_errno(m->error);
            clear_trap(&trap);
            return !errno ? 0 : -1;
        }
    }

    m = (MemoryCache *)loc_alloc_zero(sizeof(MemoryCache));
    list_add_first(&m->link_ctx, &cache->mem_cache_list);
    m->ctx = cache;
    m->addr = address;
    m->buf = loc_alloc(size);
    m->size = size;
    m->pending = protocol_send_command(c, "Memory", "get", validate_memory_cache, m);
    json_write_string(&c->out, cache->ctx->id);
    write_stream(&c->out, 0);
    json_write_int64(&c->out, m->addr);
    write_stream(&c->out, 0);
    json_write_long(&c->out, 1);
    write_stream(&c->out, 0);
    json_write_long(&c->out, m->size);
    write_stream(&c->out, 0);
    json_write_long(&c->out, 0);
    write_stream(&c->out, 0);
    write_stream(&c->out, MARKER_EOM);
    context_lock(ctx);
    cache_wait(&m->cache);
    return -1;
}

int context_write_mem(Context * ctx, ContextAddress address, void * buf, size_t size) {
    assert(0);
    errno = EINVAL;
    return -1;
}

RegisterDefinition * get_reg_by_id(Context * ctx, unsigned id, RegisterIdScope * scope) {
    RegisterDefinition * defs = get_reg_definitions(ctx);
    if (scope->machine == 3 && defs && defs->name && strcmp(defs->name, "rax") == 0) {
        /* TODO: better way to handle 32-bit ELF on X86_64 */
        switch (id) {
        case 0: /* eax */ id = 0; break;
        case 1: /* ecx */ id = 2; break;
        case 2: /* edx */ id = 1; break;
        case 3: /* ebx */ id = 3; break;
        case 4: /* esp */ id = 7; break;
        case 5: /* ebp */ id = 6; break;
        case 6: /* esi */ id = 4; break;
        case 7: /* edi */ id = 5; break;
        case 8: /* eip */ id = 16; break;
        case 9: /* eflags */ id = 49; break;
        default:
            set_errno(ERR_OTHER, "Invalid register ID");
            return NULL;
        }
    }
    while (defs != NULL && defs->name != NULL) {
        switch (scope->id_type) {
        case REGNUM_DWARF:
            if (defs->dwarf_id == (int)id) return defs;
            break;
        case REGNUM_EH_FRAME:
            if (defs->eh_frame_id == (int)id) return defs;
            break;
        }
        defs++;
    }
    set_errno(ERR_OTHER, "Invalid register ID");
    return NULL;
}

static void validate_top_frame_reg_values_cache(Channel * c, void * args, int error) {
    StackFrameCache * fc = (StackFrameCache *)args;
    RegisterDefinition * def = fc->ctx->reg_defs + fc->reg_pending;
    RegisterCache * rc = fc->reg_cache + fc->reg_pending;
    Context * ctx = fc->ctx->ctx;
    Trap trap;

    assert(fc->pending != NULL);
    assert(rc->error == NULL);
    assert(rc->valid == 0);
    if (set_trap(&trap)) {
        fc->pending = NULL;
        if (!error) {
            size_t pos = 0;
            JsonReadBinaryState state;
            error = read_errno(&c->inp);
            json_read_binary_start(&state, &c->inp);
            for (;;) {
                int rd = json_read_binary_data(&state, fc->reg_data.data + def->offset + pos, def->size - pos);
                if (rd == 0) break;
                pos += rd;
            }
            json_read_binary_end(&state);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
            memset(fc->reg_data.mask + def->offset, 0xff, pos);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    rc->valid = 1;
    rc->error = get_error_report(error);
    cache_notify_later(&fc->cache);
    if (fc->disposed) free_stack_frame_cache(fc);
    context_unlock(ctx);
}

static void validate_mid_frame_reg_values_cache(Channel * c, void * args, int error) {
    StackFrameCache * fc = (StackFrameCache *)args;
    Context * ctx = fc->ctx->ctx;
    Trap trap;

    assert(fc->pending != NULL);
    assert(fc->error == NULL);
    assert(!fc->info.is_top_frame);
    if (set_trap(&trap)) {
        fc->pending = NULL;
        if (!error) {
            int r = 0;
            int n = fc->reg_cnt;
            JsonReadBinaryState state;
            error = read_errno(&c->inp);
            json_read_binary_start(&state, &c->inp);
            for (r = 0; r < n; r++) {
                RegisterDefinition * reg = fc->reg_defs[r];
                if (reg->size > 0 && (reg->dwarf_id >= 0 || reg->role != NULL)) {
                    size_t pos = 0;
                    uint8_t * data = fc->reg_data.data + reg->offset;
                    uint8_t * mask = fc->reg_data.mask + reg->offset;
                    assert(reg->offset + reg->size <= fc->ctx->reg_size);
                    while (pos < reg->size) {
                        size_t rd = json_read_binary_data(&state, data + pos, reg->size - pos);
                        assert(pos + rd <= reg->size);
                        memset(mask + pos, ~0, rd);
                        if (rd == 0) break;
                        pos += rd;
                    }
                }
            }
            json_read_binary_end(&state);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    fc->reg_valid = 1;
    fc->error = get_error_report(error);
    cache_notify_later(&fc->cache);
    if (fc->disposed) free_stack_frame_cache(fc);
    context_unlock(ctx);
}

int read_reg_bytes(StackFrame * frame, RegisterDefinition * reg_def, unsigned offs, unsigned size, uint8_t * buf) {
    if (reg_def == NULL || frame == NULL) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    else {
        StackFrameCache * fc = (StackFrameCache *)((char *)frame - offsetof(StackFrameCache, info));
        if (frame->is_top_frame) {
            unsigned rn = reg_def - fc->ctx->reg_defs;
            if (fc->reg_cache == NULL) fc->reg_cache =
                (RegisterCache *)loc_alloc_zero(sizeof(RegisterCache) * fc->ctx->reg_max);
            assert(rn < fc->ctx->reg_max);
            if (!fc->reg_cache[rn].valid) {
                Trap trap;
                Channel * c = fc->ctx->peer->target;
                if (!set_trap(&trap)) return -1;
                if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
                if (fc->pending != NULL) cache_wait(&fc->cache);
                fc->reg_pending = rn;
                fc->pending = protocol_send_command(c, "Registers", "get", validate_top_frame_reg_values_cache, fc);
                json_write_string(&c->out, fc->ctx->reg_props[rn].id);
                write_stream(&c->out, 0);
                write_stream(&c->out, MARKER_EOM);
                context_lock(fc->ctx->ctx);
                cache_wait(&fc->cache);
                return -1;
            }
            if (fc->reg_cache[rn].error != NULL) {
                set_error_report_errno(fc->reg_cache[rn].error);
                return -1;
            }
        }
        else if (!fc->reg_valid) {
            Trap trap;
            unsigned n;
            Channel * c = fc->ctx->peer->target;
            if (!set_trap(&trap)) return -1;
            if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
            if (fc->pending != NULL) cache_wait(&fc->cache);
            fc->pending = protocol_send_command(c, "Registers", "getm", validate_mid_frame_reg_values_cache, fc);
            write_stream(&c->out, '[');
            for (n = 0; n < fc->reg_cnt; n++) {
                RegisterDefinition * reg = fc->reg_defs[n];
                if (reg->size > 0 && (reg->dwarf_id >= 0 || reg->role != NULL)) {
                    const char * id = register2id(fc->ctx->ctx, frame->frame, reg);
                    if (n > 0) write_stream(&c->out, ',');
                    write_stream(&c->out, '[');
                    json_write_string(&c->out, id);
                    write_stream(&c->out, ',');
                    json_write_long(&c->out, 0);
                    write_stream(&c->out, ',');
                    json_write_long(&c->out, reg->size);
                    write_stream(&c->out, ']');
                }
            }
            write_stream(&c->out, ']');
            write_stream(&c->out, 0);
            write_stream(&c->out, MARKER_EOM);
            context_lock(fc->ctx->ctx);
            cache_wait(&fc->cache);
            return -1;
        }
        else if (fc->error != NULL) {
            set_error_report_errno(fc->error);
            return -1;
        }
        {
            size_t i;
            uint8_t * r_addr = frame->regs->data + reg_def->offset;
            uint8_t * m_addr = frame->regs->mask + reg_def->offset;
            for (i = 0; i < size; i++) {
                if (m_addr[offs + i] != 0xff) {
                    set_fmt_errno(ERR_INV_CONTEXT, "Value of register %s is unknown in the selected frame", reg_def->name);
                    return -1;
                }
            }
            if (offs + size > reg_def->size) {
                errno = ERR_INV_DATA_SIZE;
                return -1;
            }
            memcpy(buf, r_addr + offs, size);
        }
    }
    return 0;
}

int write_reg_bytes(StackFrame * frame, RegisterDefinition * reg_def, unsigned offs, unsigned size, uint8_t * buf) {
    assert(0);
    errno = ERR_INV_CONTEXT;
    return -1;
}

int context_write_reg(Context * ctx, RegisterDefinition * def, unsigned offs, unsigned size, void * buf) {
    assert(0);
    errno = EINVAL;
    return -1;
}

int context_read_reg(Context * ctx, RegisterDefinition * def, unsigned offs, unsigned size, void * buf) {
    StackFrame * info = NULL;
    if (get_frame_info(ctx, 0, &info) < 0) return -1;
    if (read_reg_bytes(info, def, offs, size, (uint8_t *)buf) < 0) return -1;
    return 0;
}

static void read_memory_region_property(InputStream * inp, const char * name, void * args) {
    MemoryRegion * m = (MemoryRegion *)args;
    if (strcmp(name, "Addr") == 0) {
        m->addr = (ContextAddress)json_read_uint64(inp);
        m->valid |= MM_VALID_ADDR;
    }
    else if (strcmp(name, "Size") == 0) {
        m->size = json_read_ulong(inp);
        m->valid |= MM_VALID_SIZE;
    }
    else if (strcmp(name, "Offs") == 0) {
        m->file_offs = json_read_ulong(inp);
        m->valid |= MM_VALID_FILE_OFFS;
    }
    else if (strcmp(name, "FileSize") == 0) {
        m->file_size = json_read_ulong(inp);
        m->valid |= MM_VALID_FILE_SIZE;
    }
    else if (strcmp(name, "BSS") == 0) m->bss = json_read_boolean(inp);
    else if (strcmp(name, "Flags") == 0) m->flags = json_read_ulong(inp);
    else if (strcmp(name, "FileName") == 0) m->file_name = json_read_alloc_string(inp);
    else if (strcmp(name, "SectionName") == 0) m->sect_name = json_read_alloc_string(inp);
    else if (strcmp(name, "ContextQuery") == 0) m->query = json_read_alloc_string(inp);
    else if (strcmp(name, "ID") == 0) m->id = json_read_alloc_string(inp);
    else {
        MemoryRegionAttribute * x = (MemoryRegionAttribute *)loc_alloc(sizeof(MemoryRegionAttribute));
        x->name = loc_strdup(name);
        x->value = json_read_object(inp);
        x->next = m->attrs;
        m->attrs = x;
    }
}

static void read_memory_map_item(InputStream * inp, void * args) {
    ContextCache * cache = (ContextCache *)args;
    MemoryRegion * m;
    if (mem_buf_pos >= mem_buf_max) {
        mem_buf_max = mem_buf_max == 0 ? 16 : mem_buf_max * 2;
        mem_buf = (MemoryRegion *)loc_realloc(mem_buf, sizeof(MemoryRegion) * mem_buf_max);
    }
    m = mem_buf + mem_buf_pos;
    memset(m, 0, sizeof(MemoryRegion));
    if (json_read_struct(inp, read_memory_region_property, m) && m->file_name != NULL && m->file_name[0] != 0) {
        struct stat buf;
        char * fnm = apply_path_map(cache->peer->host, cache->ctx, m->file_name, PATH_MAP_TO_LOCAL);
        if (fnm != m->file_name) {
            loc_free(m->file_name);
            m->file_name = loc_strdup(canonic_path_map_file_name(fnm));
        }
        if (m->file_name != NULL && stat(m->file_name, &buf) == 0) {
            m->dev = buf.st_dev;
            m->ino = buf.st_ino;
            mem_buf_pos++;
        }
        else if (m->file_name != NULL) {
            mem_buf_pos++;
        }
    }
    if (m == mem_buf + mem_buf_pos) {
        /* Unused entry, need to free memory */
        loc_free(m->file_name);
        loc_free(m->sect_name);
        loc_free(m->query);
        loc_free(m->id);
        while (m->attrs != NULL) {
            MemoryRegionAttribute * x = m->attrs;
            m->attrs = x->next;
            loc_free(x->name);
            loc_free(x->value);
            loc_free(x);
        }
    }
}

static void validate_memory_map_cache(Channel * c, void * args, int error) {
    ContextCache * cache = (ContextCache *)args;
    Trap trap;

    assert(cache->mmap_is_valid == 0);
    assert(cache->pending_get_mmap != NULL);
    if (set_trap(&trap)) {
        cache->pending_get_mmap = NULL;
        if (!error) {
            error = read_errno(&c->inp);
            mem_buf_pos = 0;
            json_read_array(&c->inp, read_memory_map_item, cache);
            cache->target_map.region_cnt = mem_buf_pos;
            cache->target_map.region_max = mem_buf_pos;
            cache->target_map.regions = (MemoryRegion *)loc_realloc(cache->target_map.regions, sizeof(MemoryRegion) * mem_buf_pos);
            memcpy(cache->target_map.regions, mem_buf, sizeof(MemoryRegion) * mem_buf_pos);

            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    cache->mmap_is_valid = 1;
    cache->mmap_error = get_error_report(error);
    cache_notify_later(&cache->mmap_cache);
    context_unlock(cache->ctx);
}

static ContextCache * get_memory_map_cache(Context * ctx) {
    ContextCache * cache = *EXT(ctx);
    Channel * c = cache->peer->target;
    Trap trap;

    assert(cache->ctx == ctx);
    if (!set_trap(&trap)) return NULL;
    if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
    if (cache->peer != NULL && !cache->peer->rc_done) cache_wait(&cache->peer->rc_cache);

    if (cache->pending_get_mmap != NULL) cache_wait(&cache->mmap_cache);
    if (cache->mmap_is_valid == 0 && cache->peer != NULL) {
        cache->pending_get_mmap = protocol_send_command(c, MEMORY_MAP, "get", validate_memory_map_cache, cache);
        json_write_string(&c->out, cache->id);
        write_stream(&c->out, 0);
        write_stream(&c->out, MARKER_EOM);
        context_lock(ctx);
        cache_wait(&cache->mmap_cache);
    }
    clear_trap(&trap);
    if (cache->mmap_error != NULL) {
        set_error_report_errno(cache->mmap_error);
        return NULL;
    }
    cache->has_mmap = 1;
    return cache;
}

int context_get_memory_map(Context * ctx, MemoryMap * map) {
    ContextCache * cache = get_memory_map_cache(ctx);
    if (cache == NULL) return -1;
    assert(map->region_cnt == 0);
    if (map->region_max < cache->target_map.region_cnt) {
        map->region_max = cache->target_map.region_cnt;
        map->regions = (MemoryRegion *)loc_realloc(map->regions, sizeof(MemoryRegion) * map->region_max);
    }
    map->region_cnt = cache->target_map.region_cnt;
    if (map->region_cnt > 0) {
        unsigned i;
        memcpy(map->regions, cache->target_map.regions, sizeof(MemoryRegion) * map->region_cnt);
        memset(cache->target_map.regions, 0, sizeof(MemoryRegion) * map->region_cnt);
        for (i = 0; i < map->region_cnt; i++) {
            MemoryRegion * x = cache->target_map.regions + i;
            MemoryRegion * y = map->regions + i;
            if (x->file_name) y->file_name = loc_strdup(x->file_name);
            if (x->sect_name) y->sect_name = loc_strdup(x->sect_name);
            if (x->query) y->query = loc_strdup(x->query);
            if (x->id) y->id = loc_strdup(x->id);
            if (x->attrs) {
                MemoryRegionAttribute ** p = NULL;
                MemoryRegionAttribute * ax = x->attrs;
                while (ax != NULL) {
                    MemoryRegionAttribute * ay = (MemoryRegionAttribute *)
                        loc_alloc_zero(sizeof(MemoryRegionAttribute));
                    ay->name = loc_strdup(ax->name);
                    ay->value = loc_strdup(ax->value);
                    if (p == NULL) y->attrs = ay;
                    else *p = ay;
                    p = &ay->next;
                    ax = ax->next;
                }
            }
        }
    }
    return 0;
}

int memory_map_get(Context * ctx, MemoryMap ** client_map, MemoryMap ** target_map) {
    ContextCache * cache = get_memory_map_cache(ctx);
    if (cache == NULL) return -1;
    *client_map = &cache->client_map;
    *target_map = &cache->target_map;
    return 0;
}

void add_memory_map_event_listener(MemoryMapEventListener * listener, void * client_data) {
    MMListener * l = NULL;
    if (mm_listener_cnt >= mm_listener_max) {
        mm_listener_max += 8;
        mm_listeners = (MMListener *)loc_realloc(mm_listeners, mm_listener_max * sizeof(MMListener));
    }
    l = mm_listeners + mm_listener_cnt++;
    l->listener = listener;
    l->args = client_data;
}

void memory_map_event_mapping_changed(Context * ctx) {
    unsigned i;
    for (i = 0; i < mm_listener_cnt; i++) {
        MMListener * l = mm_listeners + i;
        if (l->listener->mapping_changed == NULL) continue;
        l->listener->mapping_changed(ctx, l->args);
    }
}

static void read_ids_item(InputStream * inp, void * args) {
    int n;
    char id[256];
    if (ids_buf_pos >= ids_buf_max) {
        ids_buf_max = ids_buf_max == 0 ? 16 : ids_buf_max * 2;
        ids_buf = (unsigned *)loc_realloc(ids_buf, sizeof(unsigned) * ids_buf_max);
    }
    n = json_read_string(inp, id, sizeof(id));
    if (n <= 0) return;
    n++;
    if (n > (int)sizeof(id)) n = sizeof(id);
    if (str_buf_pos + n > str_buf_max) {
        str_buf_max = str_buf_max == 0 ? sizeof(id) : str_buf_max * 2;
        str_buf = (char *)loc_realloc(str_buf, str_buf_max);
    }
    memcpy(str_buf + str_buf_pos, id, n);
    ids_buf[ids_buf_pos++] = str_buf_pos;
    str_buf_pos += n;
}

static void read_register_property(InputStream * inp, const char * name, void * args) {
    RegisterProps * p = (RegisterProps *)args;
    if (strcmp(name, "ID") == 0) p->id = json_read_alloc_string(inp);
    else if (strcmp(name, "Role") == 0) p->def.role = json_read_alloc_string(inp);
    else if (strcmp(name, "Name") == 0) p->def.name = json_read_alloc_string(inp);
    else if (strcmp(name, "Size") == 0) p->def.size = (uint16_t)json_read_long(inp);
    else if (strcmp(name, "DwarfID") == 0) p->def.dwarf_id = (int16_t)json_read_long(inp);
    else if (strcmp(name, "EhFrameID") == 0) p->def.eh_frame_id = (int16_t)json_read_long(inp);
    else if (strcmp(name, "BigEndian") == 0) p->def.big_endian = (uint8_t)json_read_boolean(inp);
    else json_skip_object(inp);
}

static unsigned get_reg_index(ContextCache * cache, const char * id) {
    unsigned r = 0;
    while (*id++ == 'R') {
        for (;;) {
            if (*id == '.' || *id == '@') {
                return r;
            }
            else if (*id >= '0' && *id <= '9') {
                r = r * 10 + (*id++ - '0');
            }
            else {
                break;
            }
        }
    }
    str_exception(ERR_OTHER, "Invalid register ID");
    return 0;
}

static void validate_registers_cache(Channel * c, void * args, int error) {
    ContextCache * cache = (ContextCache *)args;
    Trap trap;

    assert(cache->pending_regs_cnt > 0);
    cache->pending_regs_cnt--;

    if (error) {
        if (cache->reg_error == NULL) cache->reg_error = get_error_report(error);
    }
    else if (cache->reg_error != NULL) {
        int i = 0;
        do i = read_stream(&c->inp);
        while (i != MARKER_EOM && i != MARKER_EOS);
    }
    else {
        if (set_trap(&trap)) {
            error = read_errno(&c->inp);
            if (!error && peek_stream(&c->inp) == '[') {
                /* Registers.getChildren reply */
                unsigned i;
                ids_buf_pos = 0;
                str_buf_pos = 0;
                json_read_array(&c->inp, read_ids_item, NULL);
                json_test_char(&c->inp, MARKER_EOA);
                json_test_char(&c->inp, MARKER_EOM);
                for (i = 0; i < ids_buf_pos; i++) {
                    cache->pending_regs_cnt++;
                    protocol_send_command(c, "Registers", "getContext", validate_registers_cache, cache);
                    json_write_string(&c->out, str_buf + ids_buf[i]);
                    write_stream(&c->out, 0);
                    write_stream(&c->out, MARKER_EOM);
                    context_lock(cache->ctx);
                }
            }
            else if (!error && peek_stream(&c->inp) == '{') {
                /* Registers.getContext reply */
                unsigned i;
                RegisterProps props;
                memset(&props, 0, sizeof(props));
                props.def.dwarf_id = -1;
                props.def.eh_frame_id = -1;
                json_read_struct(&c->inp, read_register_property, &props);
                json_test_char(&c->inp, MARKER_EOA);
                json_test_char(&c->inp, MARKER_EOM);
                i = get_reg_index(cache, props.id);
                if (i >= cache->reg_max) {
                    unsigned pos = cache->reg_max;
                    cache->reg_max += 256;
                    if (i >= cache->reg_max) cache->reg_max = i + 2;
                    cache->reg_props = (RegisterProps *)loc_realloc(cache->reg_props, cache->reg_max * sizeof(RegisterProps));
                    cache->reg_defs = (RegisterDefinition *)loc_realloc(cache->reg_defs, cache->reg_max * sizeof(RegisterDefinition));
                    memset(cache->reg_props + pos, 0, (cache->reg_max - pos) * sizeof(RegisterProps));
                    memset(cache->reg_defs + pos, 0, (cache->reg_max - pos) * sizeof(RegisterDefinition));
                }
                cache->reg_props[i] = props;
                cache->reg_defs[i] = props.def;
                cache->pending_regs_cnt++;
                protocol_send_command(c, "Registers", "getChildren", validate_registers_cache, cache);
                json_write_string(&c->out, props.id);
                write_stream(&c->out, 0);
                write_stream(&c->out, MARKER_EOM);
                context_lock(cache->ctx);
            }
            else {
                int i = 0;
                do i = read_stream(&c->inp);
                while (i != MARKER_EOM && i != MARKER_EOS);
            }
            clear_trap(&trap);
        }
        else {
            error = trap.error;
        }
        cache->reg_error = get_error_report(error);
    }
    if (cache->pending_regs_cnt == 0) {
        unsigned i;
        unsigned offs = 0;
        for (i = 0; i < cache->reg_max; i++) {
            RegisterDefinition * r = cache->reg_defs + i;
            if (r->name != NULL) {
                r->offset = offs;
                offs += r->size;
            }
            if (r->role != NULL && strcmp(r->role, "PC") == 0) {
                cache->pc_def = r;
            }
        }
        cache->reg_size = offs;
        cache->regs_done = 1;
        cache_notify_later(&cache->regs_cache);
    }
    context_unlock(cache->ctx);
}

static void check_registers_cache(ContextCache * cache) {
    if (cache->pending_regs_cnt > 0) cache_wait(&cache->regs_cache);
    if (cache->reg_error != NULL) exception(set_error_report_errno(cache->reg_error));
    if (!cache->regs_done) {
        Channel * c = cache->peer->target;
        cache->pending_regs_cnt++;
        protocol_send_command(c, "Registers", "getChildren", validate_registers_cache, cache);
        json_write_string(&c->out, cache->ctx->id);
        write_stream(&c->out, 0);
        write_stream(&c->out, MARKER_EOM);
        context_lock(cache->ctx);
        cache_wait(&cache->regs_cache);
    }
}

RegisterDefinition * get_reg_definitions(Context * ctx) {
    ContextCache * cache = *EXT(ctx);
    check_registers_cache(cache);
    return cache->reg_defs;
}

RegisterDefinition * get_PC_definition(Context * ctx) {
    ContextCache * cache = *EXT(ctx);
    check_registers_cache(cache);
    return cache->pc_def;
}

static void validate_reg_children_cache(Channel * c, void * args, int error) {
    StackFrameCache * s = (StackFrameCache *)args;
    Context * ctx = s->ctx->ctx;
    Trap trap;

    assert(s->pending != NULL);
    assert(s->error == NULL);
    if (set_trap(&trap)) {
        s->pending = NULL;
        if (!error) {
            ids_buf_pos = 0;
            str_buf_pos = 0;
            error = read_errno(&c->inp);
            json_read_array(&c->inp, read_ids_item, NULL);
            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
            if (!error && !s->disposed) {
                unsigned n = 0;
                s->reg_cnt = ids_buf_pos;
                s->reg_defs = (RegisterDefinition **)loc_alloc_zero(sizeof(RegisterDefinition *) * s->reg_cnt);
                for (n = 0; n < s->reg_cnt; n++) {
                    char * id = str_buf + ids_buf[n];
                    unsigned r = get_reg_index(s->ctx, id);
                    s->reg_defs[n] = s->ctx->reg_defs + r;
                }
                s->info.has_reg_data = s->reg_cnt > 0;
            }
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    s->error = get_error_report(error);
    cache_notify_later(&s->cache);
    if (s->disposed) free_stack_frame_cache(s);
    context_unlock(ctx);
}

static void read_stack_frame_property(InputStream * inp, const char * name, void * args) {
    StackFrameCache * s = (StackFrameCache *)args;
    if (strcmp(name, "FP") == 0) s->info.fp = (ContextAddress)json_read_uint64(inp);
    else if (strcmp(name, "IP") == 0) s->ip = (ContextAddress)json_read_uint64(inp);
    else if (strcmp(name, "RP") == 0) s->rp = (ContextAddress)json_read_uint64(inp);
    else if (strcmp(name, "TopFrame") == 0) s->info.is_top_frame = json_read_boolean(inp);
    else if (strcmp(name, "Walk") == 0) s->info.is_walked = json_read_boolean(inp);
    else if (strcmp(name, "Inlined") == 0) s->info.inlined = (int)json_read_long(inp);
    else if (strcmp(name, "FuncID") == 0) s->info.func_id = json_read_alloc_string(inp);
    else if (strcmp(name, "CodeArea") == 0) read_code_area(inp, s->info.area = (CodeArea *)loc_alloc(sizeof(CodeArea)));
    else json_skip_object(inp);
}

static void read_stack_frame(InputStream * inp, void * args) {
    json_read_struct(inp, read_stack_frame_property, args);
}

static void validate_stack_frame_cache(Channel * c, void * args, int error) {
    StackFrameCache * s = (StackFrameCache *)args;
    Context * ctx = s->ctx->ctx;
    Trap trap;

    assert(s->pending != NULL);
    assert(s->error == NULL);
    if (set_trap(&trap)) {
        s->pending = NULL;
        if (!error) {
            json_read_array(&c->inp, read_stack_frame, s);
            json_test_char(&c->inp, MARKER_EOA);
            error = read_errno(&c->inp);
            json_test_char(&c->inp, MARKER_EOM);
            if (!error && !s->disposed && !s->info.is_top_frame) {
                s->pending = protocol_send_command(c, "Registers", "getChildren", validate_reg_children_cache, s);
                json_write_string(&c->out, frame2id(s->ctx->ctx, s->info.frame));
                write_stream(&c->out, 0);
                write_stream(&c->out, MARKER_EOM);
                clear_trap(&trap);
                return;
            }
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    s->error = get_error_report(error);
    cache_notify_later(&s->cache);
    if (s->disposed) free_stack_frame_cache(s);
    context_unlock(ctx);
}

int get_frame_info(Context * ctx, int frame, StackFrame ** info) {
    ContextCache * cache = *EXT(ctx);
    Channel * c = cache->peer->target;
    StackFrameCache * s = NULL;
    LINK * l = NULL;
    const char * id = NULL;
    Trap trap;

    if (!cache->has_state) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    if (cache->ctx->exited) {
        errno = ERR_ALREADY_EXITED;
        return -1;
    }

    if (!set_trap(&trap)) return -1;
    if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
    if (frame == STACK_TOP_FRAME) frame = 0;

    assert(frame >= 0);
    check_registers_cache(cache);
    for (l = cache->stk_cache_list.next; l != &cache->stk_cache_list; l = l->next) {
        s = ctx2stk(l);
        if (s->info.frame == frame) {
            assert(!s->disposed);
            if (s->pending != NULL) cache_wait(&s->cache);
            *info = &s->info;
            clear_trap(&trap);
            set_error_report_errno(s->error);
            return !errno ? 0 : -1;
        }
    }

    id = frame2id(cache->ctx, frame);
    if (id == NULL) {
        clear_trap(&trap);
        return -1;
    }

    s = (StackFrameCache *)loc_alloc_zero(sizeof(StackFrameCache));
    list_add_first(&s->link_ctx, &cache->stk_cache_list);
    s->ctx = cache;
    s->info.frame = frame;
    s->info.ctx = ctx;
    s->info.regs = &s->reg_data;
    s->reg_data.data = (uint8_t *)loc_alloc_zero(cache->reg_size);
    s->reg_data.mask = (uint8_t *)loc_alloc_zero(cache->reg_size);
    s->pending = protocol_send_command(c, "StackTrace", "getContext", validate_stack_frame_cache, s);
    write_stream(&c->out, '[');
    json_write_string(&c->out, id);
    write_stream(&c->out, ']');
    write_stream(&c->out, 0);
    write_stream(&c->out, MARKER_EOM);
    context_lock(ctx);
    cache_wait(&s->cache);
    return -1;
}

int get_top_frame(Context * ctx) {
    if (!ctx->stopped) {
        errno = ERR_IS_RUNNING;
        return STACK_TOP_FRAME;
    }
    return 0;
}

int get_bottom_frame(Context * ctx) {
    set_errno(ERR_UNSUPPORTED, "get_bottom_frame()");
    return STACK_BOTTOM_FRAME;
}

int get_prev_frame(Context * ctx, int frame) {
    if (frame == STACK_TOP_FRAME) {
        frame = get_top_frame(ctx);
        if (frame < 0) return frame;
    }

    if (frame < 0) {
        set_errno(ERR_OTHER, "No previous stack frame");
        return STACK_NO_FRAME;
    }

    return frame + 1;
}

int get_next_frame(Context * ctx, int frame) {
    if (frame == STACK_BOTTOM_FRAME) {
        frame = get_top_frame(ctx);
        if (frame < 0) return frame;
    }

    if (frame <= 0) {
        set_errno(ERR_OTHER, "No next stack frame");
        return STACK_NO_FRAME;
    }

    return frame - 1;
}

unsigned context_word_size(Context * ctx) {
    ContextCache * cache = *EXT(ctx);
    if (cache->word_size == 0) {
        RegisterDefinition * pc = get_PC_definition(ctx);
        cache->word_size = pc == NULL ? 4 : pc->size;
    }
    return cache->word_size;
}

#if ENABLE_ContextISA
static void read_isa_attr(InputStream * inp, const char * nm, void * args) {
    DefIsaCache * i = (DefIsaCache *)args;

    if (strcmp(nm, "DefISA") == 0) {
        i->def_isa = json_read_alloc_string(inp);
    }
    else if (strcmp(nm, "MaxInstrSize") == 0) {
        i->max_instruction_size = json_read_ulong(inp);
    }
    else if (strcmp(nm, "Alignment") == 0) {
        i->alignment = json_read_ulong(inp);
    }
    else {
        json_skip_object(inp);
    }
}

static void validate_cache_isa(Channel * c, void * args, int error) {
    DefIsaCache * i = (DefIsaCache *)args;
    Context * ctx = i->ctx->ctx;
    Trap trap;

    assert(i->pending != NULL);
    assert(i->error == NULL);

    if (set_trap(&trap)) {
        i->pending = NULL;
        if (!error) {
            error = read_errno(&c->inp);
            json_read_struct(&c->inp, read_isa_attr, i);

            json_test_char(&c->inp, MARKER_EOA);
            json_test_char(&c->inp, MARKER_EOM);
        }
        clear_trap(&trap);
    }
    else {
        error = trap.error;
    }
    i->error = get_error_report(error);
    i->isa_valid = 1;
    cache_notify_later(&i->cache);
    if (i->disposed) free_isa_cache(i);
    context_unlock(ctx);
}

static int get_context_defisa_from_rc(Context * ctx, ContextISA * isa) {
    ContextCache * cache = *EXT(ctx);
    Channel * c = cache->peer->target;
    DefIsaCache * i = NULL;
    Trap trap;

    if (cache->def_isa_cache == NULL) {
        cache->def_isa_cache = (DefIsaCache *)loc_alloc_zero(sizeof(DefIsaCache));
    }
    i = cache->def_isa_cache;

    if (!set_trap(&trap)) return -1;
    if (is_channel_closed(c)) exception(ERR_CHANNEL_CLOSED);
    if (!cache->peer->rc_done) cache_wait(&cache->peer->rc_cache);

    if (i->pending != NULL) cache_wait(&i->cache);

    if (i->isa_valid) {
        if (i->def_isa != NULL) isa->def = loc_strdup(i->def_isa);
        isa->alignment = i->alignment;
        isa->max_instruction_size = i->max_instruction_size;
        set_error_report_errno(i->error);
        clear_trap(&trap);
        return !errno ? 0 : -1;
    }

    i->ctx = cache;
    i->pending = protocol_send_command(c, "RunControl", "getISA", validate_cache_isa, i);
    json_write_string(&c->out, cache->ctx->id);
    write_stream(&c->out, 0);
    json_write_uint64(&c->out, (uint64_t)0);
    write_stream(&c->out, 0);
    write_stream(&c->out, MARKER_EOM);
    context_lock(ctx);
    cache_wait(&i->cache);
    return -1;
}

int context_get_isa(Context * ctx, ContextAddress addr, ContextISA * isa) {
    memset(isa, 0, sizeof(ContextISA));
    if (get_context_isa(ctx, addr, &isa->isa, &isa->addr, &isa->size) < 0) return -1;
    else if (isa->isa == NULL) {
        if (get_context_defisa_from_rc(ctx, isa) < 0) return -1;
    }
    return 0;
}
#endif

static void channel_close_listener(Channel * c) {
    LINK * l = NULL;

    for (l = peers.next; l != &peers; l = l->next) {
        PeerCache * p = peers2peer(l);
        if (p->target == c) {
            int i;
            assert(p->rc_pending_cnt == 0);
            for (i = 0; i < CTX_ID_HASH_SIZE; i++) {
                LINK * h = p->context_id_hash + i;
                while (!list_is_empty(h)) {
                    ContextCache * c = idhashl2ctx(h->next);
                    assert(*EXT(c->ctx) == c);
                    send_context_exited_event(c->ctx);
                }
            }
            channel_unlock(p->host);
            channel_unlock(p->target);
            cache_dispose(&p->rc_cache);
            release_error_report(p->rc_error);
            list_remove(&p->link_all);
            loc_free(p);
            return;
        }
    }
}

static void event_context_exited(Context * ctx, void * args) {
    ContextCache * c = *EXT(ctx);
    assert(!list_is_empty(&c->id_hash_link));
    list_remove(&c->id_hash_link);
}

static void event_context_disposed(Context * ctx, void * args) {
    ContextCache * c = *EXT(ctx);
    assert(c->ctx == ctx);
    c->ctx = NULL;
    free_context_cache(c);
}

static void event_path_mapping_changed(Channel * c, void * args) {
    LINK * x = context_root.next;
    while (x != &context_root) {
        Context * ctx = ctxl2ctxp(x);
        ContextCache * p = *EXT(ctx);
        clear_memory_map_data(p);
        x = x->next;
    }
}

void init_contexts_sys_dep(void) {
    static PathMapEventListener path_map_listener = {
        event_path_mapping_changed,
    };
    static ContextEventListener context_event_listener = {
        NULL,
        event_context_exited,
        NULL,
        NULL,
        NULL,
        event_context_disposed
    };
    add_path_map_event_listener(&path_map_listener, NULL);
    add_context_event_listener(&context_event_listener, NULL);
    add_channel_close_listener(channel_close_listener);
    context_extension_offset = context_extension(sizeof(ContextCache *));
}

static void command_clear(char * token, Channel * c) {
    char id[256];
    LINK * l;

    json_read_string(&c->inp, id, sizeof(id));
    json_test_char(&c->inp, MARKER_EOA);
    json_test_char(&c->inp, MARKER_EOM);

    /* Context proxy needs to clear its caches when a context is suspended temporarlily.
     * No such event is available. Only intercept is notified.
     * So, target is expected to send "ContextProxy clear <Context ID>" command
     * when a context is suspended temporarily. */

    for (l = peers.next; l != &peers; l = l->next) {
        PeerCache * p = peers2peer(l);
        if (p->host == c || p->target == c) {
            ContextCache * cache = find_context_cache(p, id);
            if (cache != NULL) {
                clear_context_suspended_data(cache);
                clear_context_cache(cache);
            }
        }
    }

    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_stream(&c->out, MARKER_EOM);
}

void ini_context_proxy_service(Protocol * proto) {
    add_command_handler(proto, CONTEXT_PROXY, "clear", command_clear);
}

#endif /* ENABLE_DebugContext && ENABLE_ContextProxy */
