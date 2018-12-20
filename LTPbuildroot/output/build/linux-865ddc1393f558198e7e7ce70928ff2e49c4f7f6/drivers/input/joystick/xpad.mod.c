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
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x92b57248, __VMLINUX_SYMBOL_STR(flush_work) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x10d5b6b6, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x6ebc1f5f, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x54b8b402, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xfaf8f001, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0x38dad6e5, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xf7dbebd5, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x5c8ff936, __VMLINUX_SYMBOL_STR(usb_wait_anchor_empty_timeout) },
	{ 0x6cc84baa, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x3bd2dceb, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xff3e3628, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x28b3c3db, __VMLINUX_SYMBOL_STR(led_set_brightness) },
	{ 0x1002eff6, __VMLINUX_SYMBOL_STR(of_led_classdev_register) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x76099a0d, __VMLINUX_SYMBOL_STR(ida_simple_get) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x610dd2ae, __VMLINUX_SYMBOL_STR(input_ff_destroy) },
	{ 0x67db99b8, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xf8ac2e35, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xf12c4c3d, __VMLINUX_SYMBOL_STR(input_ff_create_memless) },
	{ 0x34903431, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0xf811ecfb, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0x12212cd, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xdfc0c78e, __VMLINUX_SYMBOL_STR(ida_simple_remove) },
	{ 0xff8c0641, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x653e8626, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ff-memless";

MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic58isc42ip00in*");
MODULE_ALIAS("usb:v044Fp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v044Fp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v045Ep*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v045Ep*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v045Ep*d*dc*dsc*dp*icFFisc47ipD0in*");
MODULE_ALIAS("usb:v046Dp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v046Dp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v056Ep*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v056Ep*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v06A3p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v06A3p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v0738p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v0738p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v0738p4540d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0738p*d*dc*dsc*dp*icFFisc47ipD0in*");
MODULE_ALIAS("usb:v07FFp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v07FFp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v0E6Fp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v0E6Fp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v0E6Fp*d*dc*dsc*dp*icFFisc47ipD0in*");
MODULE_ALIAS("usb:v0F0Dp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v0F0Dp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v0F0Dp*d*dc*dsc*dp*icFFisc47ipD0in*");
MODULE_ALIAS("usb:v11C9p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v11C9p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v12ABp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v12ABp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v1430p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v1430p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v146Bp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v146Bp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v1532p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v1532p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v1532p*d*dc*dsc*dp*icFFisc47ipD0in*");
MODULE_ALIAS("usb:v15E4p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v15E4p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v162Ep*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v162Ep*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v1689p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v1689p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v1BADp*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v1BADp*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v24C6p*d*dc*dsc*dp*icFFisc5Dip01in*");
MODULE_ALIAS("usb:v24C6p*d*dc*dsc*dp*icFFisc5Dip81in*");
MODULE_ALIAS("usb:v24C6p*d*dc*dsc*dp*icFFisc47ipD0in*");

MODULE_INFO(srcversion, "85D9866F0D7E8D4F0C731B6");
