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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x60d060e4, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0xaa01fbfb, __VMLINUX_SYMBOL_STR(hci_recv_diag) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x815588a6, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0x870156c4, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x1de86efb, __VMLINUX_SYMBOL_STR(__hci_cmd_sync) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x8ee32459, __VMLINUX_SYMBOL_STR(__pm_runtime_use_autosuspend) },
	{ 0x97ec1ff, __VMLINUX_SYMBOL_STR(_raw_write_lock_irqsave) },
	{ 0x6a55cc0, __VMLINUX_SYMBOL_STR(hci_register_dev) },
	{ 0xd500b853, __VMLINUX_SYMBOL_STR(__pm_runtime_suspend) },
	{ 0x8d454996, __VMLINUX_SYMBOL_STR(btbcm_patchram) },
	{ 0xd8e5de5f, __VMLINUX_SYMBOL_STR(btbcm_check_bdaddr) },
	{ 0xb6e6d99d, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x33ad53d2, __VMLINUX_SYMBOL_STR(hci_reset_dev) },
	{ 0x9daa591f, __VMLINUX_SYMBOL_STR(tty_unthrottle) },
	{ 0x44dfcb74, __VMLINUX_SYMBOL_STR(btbcm_set_bdaddr) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x5641485b, __VMLINUX_SYMBOL_STR(tty_termios_encode_baud_rate) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x99ede218, __VMLINUX_SYMBOL_STR(serdev_device_close) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x317e9c3a, __VMLINUX_SYMBOL_STR(hci_recv_frame) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x46f09572, __VMLINUX_SYMBOL_STR(hci_unregister_dev) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xa120d33c, __VMLINUX_SYMBOL_STR(tty_unregister_ldisc) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x890cf5d4, __VMLINUX_SYMBOL_STR(serdev_device_write_buf) },
	{ 0xceed7f85, __VMLINUX_SYMBOL_STR(_raw_write_unlock_irqrestore) },
	{ 0x47022514, __VMLINUX_SYMBOL_STR(bt_err) },
	{ 0xd7442057, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0xd2259e55, __VMLINUX_SYMBOL_STR(serdev_device_set_tiocm) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x2f761462, __VMLINUX_SYMBOL_STR(__serdev_device_driver_register) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xe6009bcb, __VMLINUX_SYMBOL_STR(tty_ldisc_flush) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x977d4045, __VMLINUX_SYMBOL_STR(n_tty_ioctl_helper) },
	{ 0x19a78b01, __VMLINUX_SYMBOL_STR(hci_alloc_dev) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xd42c3ba7, __VMLINUX_SYMBOL_STR(serdev_device_write_flush) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x1cda20a2, __VMLINUX_SYMBOL_STR(device_property_read_u32_array) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xd8b9dad3, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x181c1c4a, __VMLINUX_SYMBOL_STR(tty_driver_flush_buffer) },
	{ 0x4558c203, __VMLINUX_SYMBOL_STR(devm_free_irq) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x7c9a7371, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0x12bde086, __VMLINUX_SYMBOL_STR(__pm_runtime_set_status) },
	{ 0x91b81412, __VMLINUX_SYMBOL_STR(devm_clk_get) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0xc76cf020, __VMLINUX_SYMBOL_STR(serdev_device_open) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb6c1e257, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0x52addd4b, __VMLINUX_SYMBOL_STR(serdev_device_set_flow_control) },
	{ 0xa657ad54, __VMLINUX_SYMBOL_STR(btbcm_initialize) },
	{ 0x9f6efab6, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x75879162, __VMLINUX_SYMBOL_STR(pm_runtime_set_autosuspend_delay) },
	{ 0x4a395dbd, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6a912370, __VMLINUX_SYMBOL_STR(btbcm_finalize) },
	{ 0x459e71da, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x144f91d9, __VMLINUX_SYMBOL_STR(hci_free_dev) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x5355c24d, __VMLINUX_SYMBOL_STR(serdev_device_set_baudrate) },
	{ 0xbed79033, __VMLINUX_SYMBOL_STR(tty_register_ldisc) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xa7fe1ea6, __VMLINUX_SYMBOL_STR(gpiod_set_value) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x4acc6ca1, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0x2ebcd9e7, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0xb98f4a8, __VMLINUX_SYMBOL_STR(tty_set_termios) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=bluetooth,btbcm,serdev";

MODULE_ALIAS("of:N*T*Cbrcm,bcm43438-bt");
MODULE_ALIAS("of:N*T*Cbrcm,bcm43438-btC*");

MODULE_INFO(srcversion, "4C52F8EA9578CE936B48C67");
