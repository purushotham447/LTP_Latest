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
	{ 0x81f8afb7, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x723cd47d, __VMLINUX_SYMBOL_STR(ovs_netdev_tunnel_destroy) },
	{ 0x5f1e4187, __VMLINUX_SYMBOL_STR(ovs_vport_ops_unregister) },
	{ 0xc9956b60, __VMLINUX_SYMBOL_STR(__ovs_vport_ops_register) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfdd412c6, __VMLINUX_SYMBOL_STR(ovs_vport_free) },
	{ 0x689c4e84, __VMLINUX_SYMBOL_STR(rtnl_delete_link) },
	{ 0x2ff812dd, __VMLINUX_SYMBOL_STR(ovs_netdev_link) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xc3aaa741, __VMLINUX_SYMBOL_STR(dev_change_flags) },
	{ 0xe2561042, __VMLINUX_SYMBOL_STR(gretap_fb_dev_create) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xfb54c1ca, __VMLINUX_SYMBOL_STR(ovs_vport_alloc) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=openvswitch,ip_gre";


MODULE_INFO(srcversion, "D78C4ABF154D014A84F625B");
