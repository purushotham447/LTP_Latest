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
	{ 0x9c74279b, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x66e2e466, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xaf2a89b1, __VMLINUX_SYMBOL_STR(em28xx_unregister_extension) },
	{ 0xa33827c0, __VMLINUX_SYMBOL_STR(em28xx_register_extension) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x518ec665, __VMLINUX_SYMBOL_STR(dvb_net_init) },
	{ 0x1ee7392b, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
	{ 0xd12b1c71, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0xd3c0a269, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x4eb1234e, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x7fc8652c, __VMLINUX_SYMBOL_STR(em28xx_tuner_callback) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x3785cc8e, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x2d038a47, __VMLINUX_SYMBOL_STR(em28xx_alloc_urbs) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x6e9dd606, __VMLINUX_SYMBOL_STR(__symbol_put) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x868784cb, __VMLINUX_SYMBOL_STR(__symbol_get) },
	{ 0xb5960baf, __VMLINUX_SYMBOL_STR(em28xx_setup_xc3028) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x721f7cc7, __VMLINUX_SYMBOL_STR(em28xx_free_device) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9e077512, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0xf10c395e, __VMLINUX_SYMBOL_STR(dvb_frontend_detach) },
	{ 0xfd967d49, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0xb554a437, __VMLINUX_SYMBOL_STR(dvb_dmx_release) },
	{ 0x220b31be, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0x432799ca, __VMLINUX_SYMBOL_STR(dvb_net_release) },
	{ 0x2a7cfbcb, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x4b462b07, __VMLINUX_SYMBOL_STR(em28xx_uninit_usb_xfer) },
	{ 0x3fed202a, __VMLINUX_SYMBOL_STR(dvb_frontend_suspend) },
	{ 0xe236709b, __VMLINUX_SYMBOL_STR(dvb_frontend_resume) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xc37c5412, __VMLINUX_SYMBOL_STR(em28xx_init_usb_xfer) },
	{ 0x8cd0b45a, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8ad855a8, __VMLINUX_SYMBOL_STR(em28xx_stop_urbs) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa2141968, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x6157e5e8, __VMLINUX_SYMBOL_STR(em28xx_write_reg) },
	{ 0xc5eb7f19, __VMLINUX_SYMBOL_STR(em28xx_gpio_set) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xf473ffaf, __VMLINUX_SYMBOL_STR(down) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xc21bbfac, __VMLINUX_SYMBOL_STR(em28xx_write_reg_bits) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0x77f4d761, __VMLINUX_SYMBOL_STR(em28xx_set_mode) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xdb290d52, __VMLINUX_SYMBOL_STR(dev_printk) },
	{ 0xd5c2f403, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=em28xx,dvb-core";


MODULE_INFO(srcversion, "FF6984310F56D5CF431A03F");
