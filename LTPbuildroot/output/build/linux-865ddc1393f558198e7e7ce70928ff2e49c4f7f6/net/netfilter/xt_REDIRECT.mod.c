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
	{ 0xe75770b6, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0xe1901a9, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0x420d2110, __VMLINUX_SYMBOL_STR(nf_nat_redirect_ipv6) },
	{ 0xc8fe12e9, __VMLINUX_SYMBOL_STR(nf_ct_netns_put) },
	{ 0xbc55b661, __VMLINUX_SYMBOL_STR(nf_nat_redirect_ipv4) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x4180f708, __VMLINUX_SYMBOL_STR(nf_ct_netns_get) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_nat_redirect,nf_conntrack";


MODULE_INFO(srcversion, "B62E5CA5ECE179965ED7C63");
