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
	{ 0x3117c537, __VMLINUX_SYMBOL_STR(deregister_mtd_parser) },
	{ 0x40a52f20, __VMLINUX_SYMBOL_STR(__register_mtd_parser) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0xf58bb32, __VMLINUX_SYMBOL_STR(of_device_is_compatible) },
	{ 0xf511a902, __VMLINUX_SYMBOL_STR(of_n_size_cells) },
	{ 0xcba01d40, __VMLINUX_SYMBOL_STR(of_n_addr_cells) },
	{ 0x4cca29e0, __VMLINUX_SYMBOL_STR(of_get_next_child) },
	{ 0x67c63256, __VMLINUX_SYMBOL_STR(of_get_child_by_name) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa6d1a808, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mtd";


MODULE_INFO(srcversion, "BDC7A03A2753FF9CF056FC8");
