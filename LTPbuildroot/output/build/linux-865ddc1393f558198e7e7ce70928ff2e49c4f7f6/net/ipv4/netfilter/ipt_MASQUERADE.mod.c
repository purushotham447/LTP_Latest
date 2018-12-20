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
	{ 0x3f5c468e, __VMLINUX_SYMBOL_STR(nf_nat_masquerade_ipv4_unregister_notifier) },
	{ 0x710a395f, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0xfedbf252, __VMLINUX_SYMBOL_STR(nf_nat_masquerade_ipv4_register_notifier) },
	{ 0xd6dac0c3, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xce2cc1ab, __VMLINUX_SYMBOL_STR(nf_nat_masquerade_ipv4) },
	{ 0x4180f708, __VMLINUX_SYMBOL_STR(nf_ct_netns_get) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc8fe12e9, __VMLINUX_SYMBOL_STR(nf_ct_netns_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_nat_masquerade_ipv4,x_tables,nf_conntrack";


MODULE_INFO(srcversion, "20A8D64485FBB65E1E9ECC2");
