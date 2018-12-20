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
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x34bbb7bb, __VMLINUX_SYMBOL_STR(tcp_reno_undo_cwnd) },
	{ 0xa80539e8, __VMLINUX_SYMBOL_STR(tcp_unregister_congestion_control) },
	{ 0x10ef1ab7, __VMLINUX_SYMBOL_STR(tcp_register_congestion_control) },
	{ 0x2910c8f2, __VMLINUX_SYMBOL_STR(tcp_cong_avoid_ai) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x1ccd51b8, __VMLINUX_SYMBOL_STR(tcp_slow_start) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "171B0F963CFE234F46B52D2");
