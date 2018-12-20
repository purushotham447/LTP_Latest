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
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x337f2432, __VMLINUX_SYMBOL_STR(l2tp_nl_unregister_ops) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x69fce13, __VMLINUX_SYMBOL_STR(l2tp_nl_register_ops) },
	{ 0x928fb09f, __VMLINUX_SYMBOL_STR(l2tp_session_delete) },
	{ 0xac4c7e42, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x358c3fd4, __VMLINUX_SYMBOL_STR(kernel_sock_ip_overhead) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x2492d879, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xedf01cff, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x375708c2, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0xe2e70b90, __VMLINUX_SYMBOL_STR(l2tp_session_create) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xa2607159, __VMLINUX_SYMBOL_STR(l2tp_xmit_skb) },
	{ 0xb4e5d113, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1043cf1e, __VMLINUX_SYMBOL_STR(__secpath_destroy) },
	{ 0x33aa810b, __VMLINUX_SYMBOL_STR(dev_forward_skb) },
	{ 0x34908c14, __VMLINUX_SYMBOL_STR(print_hex_dump_bytes) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x527cbcdf, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=l2tp_netlink,l2tp_core";


MODULE_INFO(srcversion, "1AED7D4BCD949E90326EDDE");
