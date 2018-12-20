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
	{ 0x5d72815c, __VMLINUX_SYMBOL_STR(w1_unregister_family) },
	{ 0x694436c, __VMLINUX_SYMBOL_STR(w1_register_family) },
	{ 0x7a00bec1, __VMLINUX_SYMBOL_STR(sysfs_create_bin_file) },
	{ 0xd182a85b, __VMLINUX_SYMBOL_STR(w1_write_8) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2a6ce5a, __VMLINUX_SYMBOL_STR(crc16_table) },
	{ 0x6a297b82, __VMLINUX_SYMBOL_STR(w1_read_block) },
	{ 0xe1c4e075, __VMLINUX_SYMBOL_STR(w1_write_block) },
	{ 0x3fcd8a07, __VMLINUX_SYMBOL_STR(w1_reset_select_slave) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x832f2d28, __VMLINUX_SYMBOL_STR(sysfs_remove_bin_file) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wire";


MODULE_INFO(srcversion, "6F720D901D518E5CCA0CFE9");
