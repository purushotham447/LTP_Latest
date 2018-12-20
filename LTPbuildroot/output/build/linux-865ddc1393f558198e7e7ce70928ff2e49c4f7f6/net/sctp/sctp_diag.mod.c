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
	{ 0xfdedb9c6, __VMLINUX_SYMBOL_STR(inet_diag_unregister) },
	{ 0x97013c4, __VMLINUX_SYMBOL_STR(inet_diag_register) },
	{ 0x16cd2389, __VMLINUX_SYMBOL_STR(sctp_for_each_endpoint) },
	{ 0xd9b7f07f, __VMLINUX_SYMBOL_STR(sctp_for_each_transport) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x4124ced2, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x2128367c, __VMLINUX_SYMBOL_STR(sock_diag_check_cookie) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xaaad650a, __VMLINUX_SYMBOL_STR(inet_diag_msg_common_fill) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xf6be550b, __VMLINUX_SYMBOL_STR(nla_reserve) },
	{ 0x464eb948, __VMLINUX_SYMBOL_STR(nla_reserve_64bit) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xf5c72181, __VMLINUX_SYMBOL_STR(inet_diag_msg_attrs_fill) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x78b89569, __VMLINUX_SYMBOL_STR(sock_diag_save_cookie) },
	{ 0x4620712e, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0xe3d24e5a, __VMLINUX_SYMBOL_STR(sctp_transport_lookup_process) },
	{ 0x270f0665, __VMLINUX_SYMBOL_STR(netlink_net_capable) },
	{ 0xdec79fa6, __VMLINUX_SYMBOL_STR(sctp_get_sctp_info) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=inet_diag,sctp";


MODULE_INFO(srcversion, "173155761619074A0211B3E");
