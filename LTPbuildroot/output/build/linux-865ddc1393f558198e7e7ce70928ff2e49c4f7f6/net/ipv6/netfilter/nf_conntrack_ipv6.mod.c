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
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x8525c198, __VMLINUX_SYMBOL_STR(nf_conntrack_in) },
	{ 0x37cf5b95, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_sctp6) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf137b376, __VMLINUX_SYMBOL_STR(__nf_ct_refresh_acct) },
	{ 0x8ff4678b, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_pernet_register) },
	{ 0x99bab161, __VMLINUX_SYMBOL_STR(nf_ct_zone_dflt) },
	{ 0x47ea2f3c, __VMLINUX_SYMBOL_STR(nf_ct_get_tuplepr) },
	{ 0xc093b47, __VMLINUX_SYMBOL_STR(nf_defrag_ipv6_enable) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2f772d38, __VMLINUX_SYMBOL_STR(nf_ct_deliver_cached_events) },
	{ 0xdfe41e02, __VMLINUX_SYMBOL_STR(nla_policy_len) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xa2f98d8, __VMLINUX_SYMBOL_STR(nf_log_packet) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3e1bbd5d, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_unregister) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xdd8a3d5c, __VMLINUX_SYMBOL_STR(nf_ct_invert_tuple) },
	{ 0x4b55312c, __VMLINUX_SYMBOL_STR(__nf_conntrack_confirm) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xfe2c90d1, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_pernet_unregister) },
	{ 0x44d0848a, __VMLINUX_SYMBOL_STR(nf_unregister_net_hooks) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x6f3c25d5, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_register) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb384a3e1, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_unregister) },
	{ 0xd142bfaf, __VMLINUX_SYMBOL_STR(nf_register_net_hooks) },
	{ 0x820db2a5, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0x6e224a7a, __VMLINUX_SYMBOL_STR(need_conntrack) },
	{ 0x7672f84a, __VMLINUX_SYMBOL_STR(nf_unregister_sockopt) },
	{ 0x9bb948e9, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_tcp6) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x2723eab9, __VMLINUX_SYMBOL_STR(nf_ct_seq_adjust) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x3f69cab2, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_dccp6) },
	{ 0xc4394d36, __VMLINUX_SYMBOL_STR(nf_register_sockopt) },
	{ 0x5f66d9d0, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_udp6) },
	{ 0x28e8e50d, __VMLINUX_SYMBOL_STR(proc_dointvec_jiffies) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xadfe766a, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_udplite6) },
	{ 0xf4a88c6b, __VMLINUX_SYMBOL_STR(nf_ip6_checksum) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x60688ba6, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_register) },
	{ 0x7f065e82, __VMLINUX_SYMBOL_STR(nf_conntrack_find_get) },
	{ 0x93c544ce, __VMLINUX_SYMBOL_STR(__nf_ct_l4proto_find) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_defrag_ipv6,ipv6";


MODULE_INFO(srcversion, "5152E7E48AA561F2B5BE684");
