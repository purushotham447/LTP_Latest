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
	{ 0x1c1b549c, __VMLINUX_SYMBOL_STR(class_find_device) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x4b5366cf, __VMLINUX_SYMBOL_STR(down_killable) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe93e49c3, __VMLINUX_SYMBOL_STR(devres_free) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x76099a0d, __VMLINUX_SYMBOL_STR(ida_simple_get) },
	{ 0x19465956, __VMLINUX_SYMBOL_STR(devres_alloc_node) },
	{ 0xdd9891e1, __VMLINUX_SYMBOL_STR(device_del) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe9bff861, __VMLINUX_SYMBOL_STR(down_trylock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdc781e3b, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xdfc0c78e, __VMLINUX_SYMBOL_STR(ida_simple_remove) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x2f670f3d, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0x1e445ab7, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x588913b2, __VMLINUX_SYMBOL_STR(devres_add) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x23fa0429, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xcfde09c3, __VMLINUX_SYMBOL_STR(of_parse_phandle_with_args) },
	{ 0xf8f93f90, __VMLINUX_SYMBOL_STR(of_property_match_string) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x2027510c, __VMLINUX_SYMBOL_STR(ida_destroy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "35191F5D88597E2D8B8E648");
