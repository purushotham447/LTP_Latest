#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x6d7d52d8, __VMLINUX_SYMBOL_STR(l2tp_session_free) },
	{ 0x47a547b3, __VMLINUX_SYMBOL_STR(ip_getsockopt) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa72e2aa5, __VMLINUX_SYMBOL_STR(inet_unhash) },
	{ 0x851d7300, __VMLINUX_SYMBOL_STR(ip_setsockopt) },
	{ 0xede9ebc3, __VMLINUX_SYMBOL_STR(sk_setup_caps) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf1fc9866, __VMLINUX_SYMBOL_STR(l2tp_recv_common) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xfb8a47d7, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0x4d164b6, __VMLINUX_SYMBOL_STR(inet_del_protocol) },
	{ 0x9d84537f, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0xd8ce7569, __VMLINUX_SYMBOL_STR(inet_dgram_connect) },
	{ 0x56861aec, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x4d7e95cb, __VMLINUX_SYMBOL_STR(__sock_recv_wifi_status) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x34908c14, __VMLINUX_SYMBOL_STR(print_hex_dump_bytes) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x14969c14, __VMLINUX_SYMBOL_STR(inet_addr_type) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xa3a89ec5, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0xbcc06934, __VMLINUX_SYMBOL_STR(inet_add_protocol) },
	{ 0xa889a3af, __VMLINUX_SYMBOL_STR(__sock_recv_timestamp) },
	{ 0x52aaaee1, __VMLINUX_SYMBOL_STR(inet_ioctl) },
	{ 0x1529f2d8, __VMLINUX_SYMBOL_STR(__sk_receive_skb) },
	{ 0x12e54128, __VMLINUX_SYMBOL_STR(inet_hash) },
	{ 0xad2239bf, __VMLINUX_SYMBOL_STR(ip_cmsg_recv_offset) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x1a2c2318, __VMLINUX_SYMBOL_STR(__sk_dst_check) },
	{ 0xda425d5d, __VMLINUX_SYMBOL_STR(inet_release) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0xa0f1874e, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x5d66220b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0x38a8ceb5, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x4c5fc58c, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x4c233a44, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x747fa8ee, __VMLINUX_SYMBOL_STR(inet_register_protosw) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7d564260, __VMLINUX_SYMBOL_STR(l2tp_tunnel_closeall) },
	{ 0xf13a640a, __VMLINUX_SYMBOL_STR(__udp_disconnect) },
	{ 0xcc4ac63d, __VMLINUX_SYMBOL_STR(inet_bind) },
	{ 0x2c0e20d2, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x11465467, __VMLINUX_SYMBOL_STR(__ip4_datagram_connect) },
	{ 0xddecad2c, __VMLINUX_SYMBOL_STR(sock_wmalloc) },
	{ 0x257e48da, __VMLINUX_SYMBOL_STR(l2tp_session_get) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xd27eab25, __VMLINUX_SYMBOL_STR(ip_queue_xmit) },
	{ 0x619834a1, __VMLINUX_SYMBOL_STR(inet_unregister_protosw) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=l2tp_core";


MODULE_INFO(srcversion, "C01FB0CE0F0D00D80BD6293");
