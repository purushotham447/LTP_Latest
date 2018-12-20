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
	{ 0xa72e2aa5, __VMLINUX_SYMBOL_STR(inet_unhash) },
	{ 0x6ab61ac2, __VMLINUX_SYMBOL_STR(inet6_hash) },
	{ 0xefd820b4, __VMLINUX_SYMBOL_STR(ipv6_getsockopt) },
	{ 0xce4aa77, __VMLINUX_SYMBOL_STR(ipv6_setsockopt) },
	{ 0xdb8d44cc, __VMLINUX_SYMBOL_STR(l2tp_ioctl) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0x56861aec, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0xfb8a47d7, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0x2c0e20d2, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x5d66220b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xa3a89ec5, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x19c84d5f, __VMLINUX_SYMBOL_STR(inet6_ioctl) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xd8ce7569, __VMLINUX_SYMBOL_STR(inet_dgram_connect) },
	{ 0x5981fc23, __VMLINUX_SYMBOL_STR(inet6_bind) },
	{ 0xed31f708, __VMLINUX_SYMBOL_STR(inet6_release) },
	{ 0x6249fcef, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0x3acaa1ce, __VMLINUX_SYMBOL_STR(inet6_unregister_protosw) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x2ef3cd4d, __VMLINUX_SYMBOL_STR(inet6_register_protosw) },
	{ 0xe0448517, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x9d84537f, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0x8f61d45e, __VMLINUX_SYMBOL_STR(__ip6_datagram_connect) },
	{ 0xf13a640a, __VMLINUX_SYMBOL_STR(__udp_disconnect) },
	{ 0xefa342d4, __VMLINUX_SYMBOL_STR(inet6_destroy_sock) },
	{ 0x7d564260, __VMLINUX_SYMBOL_STR(l2tp_tunnel_closeall) },
	{ 0x74f77355, __VMLINUX_SYMBOL_STR(ip6_dst_hoplimit) },
	{ 0x8b722aee, __VMLINUX_SYMBOL_STR(ip6_push_pending_frames) },
	{ 0x4670687b, __VMLINUX_SYMBOL_STR(ip6_flush_pending_frames) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x4774bf2e, __VMLINUX_SYMBOL_STR(ip6_append_data) },
	{ 0xcbf31d70, __VMLINUX_SYMBOL_STR(ip_generic_getfrag) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa621670, __VMLINUX_SYMBOL_STR(ip6_dst_lookup_flow) },
	{ 0x293a9ef6, __VMLINUX_SYMBOL_STR(fl6_update_dst) },
	{ 0x573b5453, __VMLINUX_SYMBOL_STR(ipv6_fixup_options) },
	{ 0xdc07e334, __VMLINUX_SYMBOL_STR(fl6_merge_options) },
	{ 0xccd46180, __VMLINUX_SYMBOL_STR(ip6_datagram_send_ctl) },
	{ 0x562656f7, __VMLINUX_SYMBOL_STR(fl6_sock_lookup) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1d7d6d93, __VMLINUX_SYMBOL_STR(ip6_datagram_recv_ctl) },
	{ 0x4d7e95cb, __VMLINUX_SYMBOL_STR(__sock_recv_wifi_status) },
	{ 0xa889a3af, __VMLINUX_SYMBOL_STR(__sock_recv_timestamp) },
	{ 0x2383a6b5, __VMLINUX_SYMBOL_STR(ipv6_recv_error) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xeb33231e, __VMLINUX_SYMBOL_STR(ipv6_chk_addr) },
	{ 0x684ca8f3, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x1529f2d8, __VMLINUX_SYMBOL_STR(__sk_receive_skb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x38a8ceb5, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x4c233a44, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x4c5fc58c, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x6d7d52d8, __VMLINUX_SYMBOL_STR(l2tp_session_free) },
	{ 0xf1fc9866, __VMLINUX_SYMBOL_STR(l2tp_recv_common) },
	{ 0x34908c14, __VMLINUX_SYMBOL_STR(print_hex_dump_bytes) },
	{ 0x257e48da, __VMLINUX_SYMBOL_STR(l2tp_session_get) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ipv6,l2tp_ip,l2tp_core";


MODULE_INFO(srcversion, "7728D5EADBD50EB7BF21105");
