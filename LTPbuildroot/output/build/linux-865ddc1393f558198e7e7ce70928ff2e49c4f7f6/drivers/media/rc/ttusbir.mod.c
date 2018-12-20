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
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xdfd0c515, __VMLINUX_SYMBOL_STR(rc_register_device) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x1002eff6, __VMLINUX_SYMBOL_STR(of_led_classdev_register) },
	{ 0xfaf8f001, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x54b8b402, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x8cd0b45a, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0x7b6fd1e, __VMLINUX_SYMBOL_STR(rc_free_device) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf76fb8be, __VMLINUX_SYMBOL_STR(rc_allocate_device) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa03a144b, __VMLINUX_SYMBOL_STR(ir_raw_event_handle) },
	{ 0x1e659436, __VMLINUX_SYMBOL_STR(ir_raw_event_store_with_filter) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfaa1ad97, __VMLINUX_SYMBOL_STR(usb_unlink_urb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x6ebc1f5f, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x10d5b6b6, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xff8c0641, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x4d4db2b0, __VMLINUX_SYMBOL_STR(rc_unregister_device) },
	{ 0xfd0a9a61, __VMLINUX_SYMBOL_STR(led_classdev_suspend) },
	{ 0x653e8626, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x486c9fe6, __VMLINUX_SYMBOL_STR(led_classdev_resume) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0B48p2003d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "4E00B6AAC01A9F2AB2B7E9D");
