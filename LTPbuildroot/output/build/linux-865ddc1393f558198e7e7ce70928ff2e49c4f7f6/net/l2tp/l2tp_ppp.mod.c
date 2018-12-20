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
	{ 0x928fb09f, __VMLINUX_SYMBOL_STR(l2tp_session_delete) },
	{ 0xe37ae932, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x5e9431b, __VMLINUX_SYMBOL_STR(pppox_ioctl) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x337f2432, __VMLINUX_SYMBOL_STR(l2tp_nl_unregister_ops) },
	{ 0x53b0e41, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0xe0ff7a18, __VMLINUX_SYMBOL_STR(unregister_pppox_proto) },
	{ 0x69fce13, __VMLINUX_SYMBOL_STR(l2tp_nl_register_ops) },
	{ 0x29419687, __VMLINUX_SYMBOL_STR(register_pppox_proto) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x3828f72e, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x5ef2382d, __VMLINUX_SYMBOL_STR(l2tp_session_set_header_len) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x22e191c9, __VMLINUX_SYMBOL_STR(l2tp_session_get_nth) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x3c6c56c9, __VMLINUX_SYMBOL_STR(ppp_input) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0xa3a89ec5, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x71100ac, __VMLINUX_SYMBOL_STR(l2tp_tunnel_find_nth) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xf29305c4, __VMLINUX_SYMBOL_STR(ppp_dev_name) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xa86cdd09, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0x2a628db, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x12c0d1f2, __VMLINUX_SYMBOL_STR(l2tp_session_queue_purge) },
	{ 0x32aa1872, __VMLINUX_SYMBOL_STR(__l2tp_session_unhash) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x190a3c9e, __VMLINUX_SYMBOL_STR(pppox_unbind_sock) },
	{ 0xecd3954c, __VMLINUX_SYMBOL_STR(l2tp_tunnel_create) },
	{ 0x63b46f30, __VMLINUX_SYMBOL_STR(ppp_register_net_channel) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x5ab64463, __VMLINUX_SYMBOL_STR(l2tp_tunnel_get) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xf4c95eee, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0xa2607159, __VMLINUX_SYMBOL_STR(l2tp_xmit_skb) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xddecad2c, __VMLINUX_SYMBOL_STR(sock_wmalloc) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x95893078, __VMLINUX_SYMBOL_STR(l2tp_udp_encap_recv) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x6d7d52d8, __VMLINUX_SYMBOL_STR(l2tp_session_free) },
	{ 0x257e48da, __VMLINUX_SYMBOL_STR(l2tp_session_get) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe2e70b90, __VMLINUX_SYMBOL_STR(l2tp_session_create) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=l2tp_core,pppox,l2tp_netlink,ppp_generic";


MODULE_INFO(srcversion, "E27D19C61863B73892D5AD9");
