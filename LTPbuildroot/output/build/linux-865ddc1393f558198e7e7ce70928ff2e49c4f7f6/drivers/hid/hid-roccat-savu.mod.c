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
	{ 0x79b5cf14, __VMLINUX_SYMBOL_STR(hid_unregister_driver) },
	{ 0xad050f2b, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x36f3673a, __VMLINUX_SYMBOL_STR(__hid_register_driver) },
	{ 0x65961174, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xc2c72b62, __VMLINUX_SYMBOL_STR(roccat_connect) },
	{ 0x3f79398, __VMLINUX_SYMBOL_STR(roccat_common2_device_init_struct) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x83560cf8, __VMLINUX_SYMBOL_STR(hid_hw_start) },
	{ 0x8811ec8c, __VMLINUX_SYMBOL_STR(hid_open_report) },
	{ 0x3797c7ac, __VMLINUX_SYMBOL_STR(roccat_common2_sysfs_read) },
	{ 0xead5dddb, __VMLINUX_SYMBOL_STR(roccat_common2_sysfs_write) },
	{ 0x2f622ea1, __VMLINUX_SYMBOL_STR(roccat_disconnect) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd664d17a, __VMLINUX_SYMBOL_STR(hid_hw_stop) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x8c4181ec, __VMLINUX_SYMBOL_STR(roccat_report_event) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=hid-roccat,hid-roccat-common";

MODULE_ALIAS("hid:b0003g*v00001E7Dp00002D5A");

MODULE_INFO(srcversion, "BFA44DDC425EFC8C6D8A11F");
