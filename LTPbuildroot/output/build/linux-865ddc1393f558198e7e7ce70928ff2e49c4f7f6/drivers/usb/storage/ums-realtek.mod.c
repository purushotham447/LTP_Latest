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
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xd0cc1e2, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_buf) },
	{ 0x93f258cb, __VMLINUX_SYMBOL_STR(usb_stor_post_reset) },
	{ 0xddaf5269, __VMLINUX_SYMBOL_STR(usb_stor_control_msg) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xcdb2fd03, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0x37c3325b, __VMLINUX_SYMBOL_STR(usb_enable_autosuspend) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x575a8fda, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xe5bd9e39, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface_async) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb6dc7482, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x84e8a6f3, __VMLINUX_SYMBOL_STR(usb_stor_host_template_init) },
	{ 0x7894cfb3, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x6dc5fbe3, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x9eec27a5, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0xefe0bb4a, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x75879162, __VMLINUX_SYMBOL_STR(pm_runtime_set_autosuspend_delay) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0BDAp0138d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp0158d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp0159d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "E305CBB8A937E1AB7112483");
