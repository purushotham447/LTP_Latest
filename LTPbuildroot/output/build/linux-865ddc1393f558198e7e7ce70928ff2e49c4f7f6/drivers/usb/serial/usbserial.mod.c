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
	{ 0xf4a5be32, __VMLINUX_SYMBOL_STR(tty_port_tty_get) },
	{ 0x6d662533, __VMLINUX_SYMBOL_STR(_find_first_bit_le) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xd961f31b, __VMLINUX_SYMBOL_STR(bus_register) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x4a00e865, __VMLINUX_SYMBOL_STR(driver_register) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0x93bf7c0e, __VMLINUX_SYMBOL_STR(idr_alloc_cmn) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc068440e, __VMLINUX_SYMBOL_STR(__kfifo_alloc) },
	{ 0x7647726c, __VMLINUX_SYMBOL_STR(handle_sysrq) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x38c9d41c, __VMLINUX_SYMBOL_STR(radix_tree_delete_item) },
	{ 0xec655690, __VMLINUX_SYMBOL_STR(tty_port_open) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xacb784b1, __VMLINUX_SYMBOL_STR(tty_port_hangup) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x653e8626, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x307f8d51, __VMLINUX_SYMBOL_STR(tty_register_driver) },
	{ 0xcdb2fd03, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x449c0ca2, __VMLINUX_SYMBOL_STR(put_tty_driver) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xa32b9eb2, __VMLINUX_SYMBOL_STR(tty_set_operations) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x56d44447, __VMLINUX_SYMBOL_STR(__tty_insert_flip_char) },
	{ 0x8c56c82e, __VMLINUX_SYMBOL_STR(tty_port_close) },
	{ 0xd6387855, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0xdd9891e1, __VMLINUX_SYMBOL_STR(device_del) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7b3ce010, __VMLINUX_SYMBOL_STR(tty_ldisc_deref) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x9678c31, __VMLINUX_SYMBOL_STR(usb_unpoison_urb) },
	{ 0xc8126f9, __VMLINUX_SYMBOL_STR(usb_poison_urb) },
	{ 0xd8477f69, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0xe63799f, __VMLINUX_SYMBOL_STR(tty_port_init) },
	{ 0xa615b2d8, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_fixed_flag) },
	{ 0xfb19755, __VMLINUX_SYMBOL_STR(tty_port_destroy) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xcbc507cf, __VMLINUX_SYMBOL_STR(tty_vhangup) },
	{ 0xaf9787a7, __VMLINUX_SYMBOL_STR(tty_ldisc_ref) },
	{ 0x2f670f3d, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0xd40d41d4, __VMLINUX_SYMBOL_STR(bus_unregister) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xff4f05b4, __VMLINUX_SYMBOL_STR(usb_store_new_id) },
	{ 0xab45e185, __VMLINUX_SYMBOL_STR(usb_match_id) },
	{ 0xd3c8bc70, __VMLINUX_SYMBOL_STR(tty_register_device) },
	{ 0x4936ceb4, __VMLINUX_SYMBOL_STR(tty_port_tty_wakeup) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x9e9d444f, __VMLINUX_SYMBOL_STR(tty_unregister_device) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
	{ 0x7cb06319, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x3fb768dd, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xf091f724, __VMLINUX_SYMBOL_STR(tty_port_install) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x3efa96a4, __VMLINUX_SYMBOL_STR(usb_get_intf) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x30e74134, __VMLINUX_SYMBOL_STR(tty_termios_copy_hw) },
	{ 0xdb760f52, __VMLINUX_SYMBOL_STR(__kfifo_free) },
	{ 0x5869e8b6, __VMLINUX_SYMBOL_STR(tty_unregister_driver) },
	{ 0xde45dd6d, __VMLINUX_SYMBOL_STR(tty_hangup) },
	{ 0x694be42a, __VMLINUX_SYMBOL_STR(usb_show_dynids) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x5b5c81ad, __VMLINUX_SYMBOL_STR(__tty_alloc_driver) },
	{ 0x19a304ba, __VMLINUX_SYMBOL_STR(usb_disabled) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x54496b4, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x23fa0429, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0xbb26a954, __VMLINUX_SYMBOL_STR(usb_match_one_id) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xb8eec15d, __VMLINUX_SYMBOL_STR(tty_kref_put) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xb86d6479, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x2369d856, __VMLINUX_SYMBOL_STR(driver_attach) },
	{ 0x1a752e48, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0xf23fcb99, __VMLINUX_SYMBOL_STR(__kfifo_in) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x8d13991e, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x6ebc1f5f, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x44e0f020, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x54b8b402, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xa1a1d62c, __VMLINUX_SYMBOL_STR(usb_put_intf) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DD0BBA6D091CAC0A0AC1DD8");
