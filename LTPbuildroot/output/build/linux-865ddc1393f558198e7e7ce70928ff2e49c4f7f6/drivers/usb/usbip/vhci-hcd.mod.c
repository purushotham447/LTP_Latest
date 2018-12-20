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
	{ 0x5a02e2b6, __VMLINUX_SYMBOL_STR(usbip_event_happened) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x5eaa4cf3, __VMLINUX_SYMBOL_STR(usb_create_shared_hcd) },
	{ 0xd02753dc, __VMLINUX_SYMBOL_STR(usbip_header_correct_endian) },
	{ 0x7c0a1fb, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0xed874ab8, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0x607ff2b5, __VMLINUX_SYMBOL_STR(usb_add_hcd) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x179e3e9b, __VMLINUX_SYMBOL_STR(usb_remove_hcd) },
	{ 0x5a2ca832, __VMLINUX_SYMBOL_STR(usb_create_hcd) },
	{ 0x373276b, __VMLINUX_SYMBOL_STR(usb_hcd_poll_rh_status) },
	{ 0x3ff05adb, __VMLINUX_SYMBOL_STR(usbip_alloc_iso_desc_pdu) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xf5d37a74, __VMLINUX_SYMBOL_STR(usb_hcd_giveback_urb) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x456913ac, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x27168320, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x2c331061, __VMLINUX_SYMBOL_STR(usb_put_hcd) },
	{ 0x3966c7cf, __VMLINUX_SYMBOL_STR(usbip_event_add) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe7218347, __VMLINUX_SYMBOL_STR(usb_hcd_is_primary_hcd) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xe1ea0586, __VMLINUX_SYMBOL_STR(usbip_dump_header) },
	{ 0x77ae495d, __VMLINUX_SYMBOL_STR(usb_speed_string) },
	{ 0x8ec7fbc7, __VMLINUX_SYMBOL_STR(usb_hcd_link_urb_to_ep) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xf14c5dcc, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xdcab5c07, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x11a13e31, __VMLINUX_SYMBOL_STR(_kstrtol) },
	{ 0x6bcbd7a5, __VMLINUX_SYMBOL_STR(platform_device_del) },
	{ 0x5093815e, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xba2873be, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0x55555e79, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xaef590b5, __VMLINUX_SYMBOL_STR(usbip_stop_eh) },
	{ 0xe341f5e3, __VMLINUX_SYMBOL_STR(dev_attr_usbip_debug) },
	{ 0x4e3024ae, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0x373db350, __VMLINUX_SYMBOL_STR(kstrtoint) },
	{ 0x38bbb804, __VMLINUX_SYMBOL_STR(sysfs_remove_link) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x5b85876, __VMLINUX_SYMBOL_STR(usbip_recv_iso) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x9b3de4f, __VMLINUX_SYMBOL_STR(usbip_pad_iso) },
	{ 0x1aa237fc, __VMLINUX_SYMBOL_STR(usb_hcd_check_unlink_urb) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xb3634b4f, __VMLINUX_SYMBOL_STR(usbip_dump_urb) },
	{ 0x7cb06319, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xf4aba27a, __VMLINUX_SYMBOL_STR(usbip_recv) },
	{ 0x3fb768dd, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0xf4bfa21, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x8bd5ef71, __VMLINUX_SYMBOL_STR(platform_bus) },
	{ 0x9df4100f, __VMLINUX_SYMBOL_STR(platform_device_add_data) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x19a304ba, __VMLINUX_SYMBOL_STR(usb_disabled) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xc4167952, __VMLINUX_SYMBOL_STR(usbip_recv_xbuff) },
	{ 0x5012c033, __VMLINUX_SYMBOL_STR(__put_task_struct) },
	{ 0x78b72f44, __VMLINUX_SYMBOL_STR(usbip_debug_flag) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xc3c30907, __VMLINUX_SYMBOL_STR(usb_hcd_unlink_urb_from_ep) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xeffc5603, __VMLINUX_SYMBOL_STR(usb_hcd_resume_root_hub) },
	{ 0xca9b8ca, __VMLINUX_SYMBOL_STR(usbip_start_eh) },
	{ 0xf0ea4344, __VMLINUX_SYMBOL_STR(usbip_pack_pdu) },
	{ 0x6192ce5a, __VMLINUX_SYMBOL_STR(platform_device_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbip-core";


MODULE_INFO(srcversion, "D71E80A7C749E25E572A339");
