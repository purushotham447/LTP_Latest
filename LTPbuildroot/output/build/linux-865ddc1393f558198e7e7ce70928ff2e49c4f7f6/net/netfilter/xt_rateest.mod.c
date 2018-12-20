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
	{ 0x458f7cd6, __VMLINUX_SYMBOL_STR(xt_unregister_match) },
	{ 0x272ea3a8, __VMLINUX_SYMBOL_STR(xt_register_match) },
	{ 0x4df2ea84, __VMLINUX_SYMBOL_STR(gen_estimator_read) },
	{ 0x4bc67fb3, __VMLINUX_SYMBOL_STR(xt_rateest_lookup) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x96641eab, __VMLINUX_SYMBOL_STR(xt_rateest_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,xt_RATEEST";


MODULE_INFO(srcversion, "56CE0D90FA4E874C6F3E2DC");
