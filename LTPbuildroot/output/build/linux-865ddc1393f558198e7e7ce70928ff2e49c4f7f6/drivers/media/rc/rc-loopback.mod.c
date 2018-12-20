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
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x4d4db2b0, __VMLINUX_SYMBOL_STR(rc_unregister_device) },
	{ 0x7b6fd1e, __VMLINUX_SYMBOL_STR(rc_free_device) },
	{ 0xdfd0c515, __VMLINUX_SYMBOL_STR(rc_register_device) },
	{ 0xf76fb8be, __VMLINUX_SYMBOL_STR(rc_allocate_device) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xba9568d4, __VMLINUX_SYMBOL_STR(ir_raw_event_store) },
	{ 0x5b304181, __VMLINUX_SYMBOL_STR(ir_raw_encode_scancode) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa03a144b, __VMLINUX_SYMBOL_STR(ir_raw_event_handle) },
	{ 0x1e659436, __VMLINUX_SYMBOL_STR(ir_raw_event_store_with_filter) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3B3DE577D887E7A3AC6F4E4");
