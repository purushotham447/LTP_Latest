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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xedc33a11, __VMLINUX_SYMBOL_STR(usb_stor_set_xfer_buf) },
	{ 0xd0cc1e2, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_buf) },
	{ 0x6aa584fc, __VMLINUX_SYMBOL_STR(usb_stor_access_xfer_buf) },
	{ 0x93f258cb, __VMLINUX_SYMBOL_STR(usb_stor_post_reset) },
	{ 0x90473e4e, __VMLINUX_SYMBOL_STR(usb_reset_configuration) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x575a8fda, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb6dc7482, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0x298425ff, __VMLINUX_SYMBOL_STR(fill_inquiry_response) },
	{ 0x84e8a6f3, __VMLINUX_SYMBOL_STR(usb_stor_host_template_init) },
	{ 0x6dc5fbe3, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x9eec27a5, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0x9f4c4934, __VMLINUX_SYMBOL_STR(usb_stor_ctrl_transfer) },
	{ 0xdc332d8f, __VMLINUX_SYMBOL_STR(usb_stor_suspend) },
	{ 0xb746e470, __VMLINUX_SYMBOL_STR(usb_stor_CB_reset) },
	{ 0xefe0bb4a, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xdea999dc, __VMLINUX_SYMBOL_STR(usb_stor_resume) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xe7eb7b66, __VMLINUX_SYMBOL_STR(usb_stor_CB_transport) },
	{ 0x82d1c76b, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_sg) },
	{ 0x48bb039a, __VMLINUX_SYMBOL_STR(usb_stor_bulk_srb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0436p0005d0100dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04E6p0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04E6p0005d020[0-8]dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04E6p0005d01*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v066Bp0105d0100dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0781p0200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07AFp0006d0100dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "A3F5E961D7275C58366CE9C");
