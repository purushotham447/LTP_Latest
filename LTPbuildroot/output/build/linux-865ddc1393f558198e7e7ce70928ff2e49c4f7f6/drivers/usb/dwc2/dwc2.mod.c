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
	{ 0xb077e70a, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0x90e32429, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x29552720, __VMLINUX_SYMBOL_STR(usb_gadget_map_request) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x2ee0613d, __VMLINUX_SYMBOL_STR(dma_release_from_dev_coherent) },
	{ 0x815588a6, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0xeb03b389, __VMLINUX_SYMBOL_STR(__raw_readsl) },
	{ 0x607ff2b5, __VMLINUX_SYMBOL_STR(usb_add_hcd) },
	{ 0x6f7f1a6f, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x9b99c606, __VMLINUX_SYMBOL_STR(usb_hcd_unmap_urb_for_dma) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x179e3e9b, __VMLINUX_SYMBOL_STR(usb_remove_hcd) },
	{ 0xea124bd1, __VMLINUX_SYMBOL_STR(gcd) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x43c91d37, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x5a2ca832, __VMLINUX_SYMBOL_STR(usb_create_hcd) },
	{ 0xb6e6d99d, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x3f63b8a3, __VMLINUX_SYMBOL_STR(usb_del_gadget_udc) },
	{ 0xa96bd1f, __VMLINUX_SYMBOL_STR(usb_gadget_giveback_request) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x7bf368c1, __VMLINUX_SYMBOL_STR(devm_ioremap_resource) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xf5d37a74, __VMLINUX_SYMBOL_STR(usb_hcd_giveback_urb) },
	{ 0x2c346f30, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x922f45a6, __VMLINUX_SYMBOL_STR(__bitmap_clear) },
	{ 0x60ceba45, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x93ee4398, __VMLINUX_SYMBOL_STR(usb_hub_clear_tt_buffer) },
	{ 0x2c331061, __VMLINUX_SYMBOL_STR(usb_put_hcd) },
	{ 0x71f499f6, __VMLINUX_SYMBOL_STR(devm_regulator_bulk_get) },
	{ 0x3a6f0594, __VMLINUX_SYMBOL_STR(regulator_bulk_enable) },
	{ 0x3d92850a, __VMLINUX_SYMBOL_STR(dma_alloc_from_dev_coherent) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xbf9bcef9, __VMLINUX_SYMBOL_STR(usb_gadget_unmap_request) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xc4629250, __VMLINUX_SYMBOL_STR(dmam_free_coherent) },
	{ 0x77ae495d, __VMLINUX_SYMBOL_STR(usb_speed_string) },
	{ 0x8ec7fbc7, __VMLINUX_SYMBOL_STR(usb_hcd_link_urb_to_ep) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x64127b67, __VMLINUX_SYMBOL_STR(bitmap_find_next_zero_area_off) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x18bd76a4, __VMLINUX_SYMBOL_STR(_raw_spin_trylock) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x7c228d48, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x75a8204c, __VMLINUX_SYMBOL_STR(device_property_read_string) },
	{ 0x7e64181d, __VMLINUX_SYMBOL_STR(usb_calc_bus_time) },
	{ 0x8c9201a, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x809e3303, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe523ad75, __VMLINUX_SYMBOL_STR(synchronize_irq) },
	{ 0x1aa237fc, __VMLINUX_SYMBOL_STR(usb_hcd_check_unlink_urb) },
	{ 0x615911d7, __VMLINUX_SYMBOL_STR(__bitmap_set) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x9a4cb0e0, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xa5cc9d8, __VMLINUX_SYMBOL_STR(debugfs_create_regset32) },
	{ 0x1cda20a2, __VMLINUX_SYMBOL_STR(device_property_read_u32_array) },
	{ 0x9a83d378, __VMLINUX_SYMBOL_STR(regulator_bulk_disable) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x260a33e8, __VMLINUX_SYMBOL_STR(usb_add_gadget_udc) },
	{ 0x58d2273e, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xf1ea0c80, __VMLINUX_SYMBOL_STR(usb_hcd_map_urb_for_dma) },
	{ 0x7c9a7371, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xda3e85c7, __VMLINUX_SYMBOL_STR(usb_ep_set_maxpacket_limit) },
	{ 0xff732a7, __VMLINUX_SYMBOL_STR(usb_get_dr_mode) },
	{ 0x91b81412, __VMLINUX_SYMBOL_STR(devm_clk_get) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x73ad200d, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0xecf8a3b4, __VMLINUX_SYMBOL_STR(__raw_writesl) },
	{ 0x19a304ba, __VMLINUX_SYMBOL_STR(usb_disabled) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x459e71da, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xc3c30907, __VMLINUX_SYMBOL_STR(usb_hcd_unlink_urb_from_ep) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xeffc5603, __VMLINUX_SYMBOL_STR(usb_hcd_resume_root_hub) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0x4acc6ca1, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0xf692c42e, __VMLINUX_SYMBOL_STR(dmam_alloc_coherent) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=udc-core";

MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-usb");
MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-usbC*");
MODULE_ALIAS("of:N*T*Chisilicon,hi6220-usb");
MODULE_ALIAS("of:N*T*Chisilicon,hi6220-usbC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-usb");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-usbC*");
MODULE_ALIAS("of:N*T*Clantiq,arx100-usb");
MODULE_ALIAS("of:N*T*Clantiq,arx100-usbC*");
MODULE_ALIAS("of:N*T*Clantiq,xrx200-usb");
MODULE_ALIAS("of:N*T*Clantiq,xrx200-usbC*");
MODULE_ALIAS("of:N*T*Csnps,dwc2");
MODULE_ALIAS("of:N*T*Csnps,dwc2C*");
MODULE_ALIAS("of:N*T*Csamsung,s3c6400-hsotg");
MODULE_ALIAS("of:N*T*Csamsung,s3c6400-hsotgC*");
MODULE_ALIAS("of:N*T*Camlogic,meson8-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson8-usbC*");
MODULE_ALIAS("of:N*T*Camlogic,meson8b-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson8b-usbC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-usbC*");
MODULE_ALIAS("of:N*T*Camcc,dwc-otg");
MODULE_ALIAS("of:N*T*Camcc,dwc-otgC*");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-fsotg");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-fsotgC*");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-hsotg");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-hsotgC*");

MODULE_INFO(srcversion, "20E2CCD6AEA6D0681B80D84");
