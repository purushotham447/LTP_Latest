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
	{ 0xc56a7c0c, __VMLINUX_SYMBOL_STR(inet_diag_dump_icsk) },
	{ 0xfc4f3b8e, __VMLINUX_SYMBOL_STR(inet_diag_dump_one_icsk) },
	{ 0x8a69a114, __VMLINUX_SYMBOL_STR(tcp_hashinfo) },
	{ 0x3d8aaebd, __VMLINUX_SYMBOL_STR(tcp_get_info) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=inet_diag";


MODULE_INFO(srcversion, "C18ECD58812E8C2BF9B891D");
