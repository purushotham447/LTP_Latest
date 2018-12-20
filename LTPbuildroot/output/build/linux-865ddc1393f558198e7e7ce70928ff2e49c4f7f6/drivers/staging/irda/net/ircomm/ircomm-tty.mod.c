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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf4a5be32, __VMLINUX_SYMBOL_STR(tty_port_tty_get) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb9394173, __VMLINUX_SYMBOL_STR(irias_delete_value) },
	{ 0x91815586, __VMLINUX_SYMBOL_STR(irda_param_pack) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x150b0712, __VMLINUX_SYMBOL_STR(tty_port_close_end) },
	{ 0x763e54a4, __VMLINUX_SYMBOL_STR(irlmp_unregister_client) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xf8378886, __VMLINUX_SYMBOL_STR(tty_hung_up_p) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x8982c8d9, __VMLINUX_SYMBOL_STR(irias_delete_object) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x307f8d51, __VMLINUX_SYMBOL_STR(tty_register_driver) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xfdd314bc, __VMLINUX_SYMBOL_STR(tty_port_carrier_raised) },
	{ 0x449c0ca2, __VMLINUX_SYMBOL_STR(put_tty_driver) },
	{ 0xa02f4cb6, __VMLINUX_SYMBOL_STR(tty_port_close_start) },
	{ 0x1ce82431, __VMLINUX_SYMBOL_STR(ircomm_connect_response) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xf199cba4, __VMLINUX_SYMBOL_STR(irias_insert_object) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xa32b9eb2, __VMLINUX_SYMBOL_STR(tty_set_operations) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xf9562325, __VMLINUX_SYMBOL_STR(iriap_getvaluebyclass_request) },
	{ 0x7042bc54, __VMLINUX_SYMBOL_STR(irlmp_register_client) },
	{ 0xaad8c7d6, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x8a44dd5e, __VMLINUX_SYMBOL_STR(hashbin_new) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x6b76aa70, __VMLINUX_SYMBOL_STR(hashbin_delete) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa464d081, __VMLINUX_SYMBOL_STR(ircomm_disconnect_request) },
	{ 0x6492e28c, __VMLINUX_SYMBOL_STR(hashbin_get_next) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xd8477f69, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xe63799f, __VMLINUX_SYMBOL_STR(tty_port_init) },
	{ 0x94a824db, __VMLINUX_SYMBOL_STR(irda_param_extract_all) },
	{ 0xa615b2d8, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_fixed_flag) },
	{ 0xfb19755, __VMLINUX_SYMBOL_STR(tty_port_destroy) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x7d3647c, __VMLINUX_SYMBOL_STR(irlmp_register_service) },
	{ 0x7d032258, __VMLINUX_SYMBOL_STR(ircomm_connect_request) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x181c1c4a, __VMLINUX_SYMBOL_STR(tty_driver_flush_buffer) },
	{ 0xb3c13d7f, __VMLINUX_SYMBOL_STR(irias_add_integer_attrib) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x37791344, __VMLINUX_SYMBOL_STR(hashbin_get_first) },
	{ 0xe24fe385, __VMLINUX_SYMBOL_STR(iriap_close) },
	{ 0xbe40ace9, __VMLINUX_SYMBOL_STR(irlmp_discovery_request) },
	{ 0xf091f724, __VMLINUX_SYMBOL_STR(tty_port_install) },
	{ 0x9ee0f7a1, __VMLINUX_SYMBOL_STR(irda_notify_init) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x5869e8b6, __VMLINUX_SYMBOL_STR(tty_unregister_driver) },
	{ 0x17a491c5, __VMLINUX_SYMBOL_STR(irias_add_octseq_attrib) },
	{ 0xde45dd6d, __VMLINUX_SYMBOL_STR(tty_hangup) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x365b41f1, __VMLINUX_SYMBOL_STR(tty_port_tty_hangup) },
	{ 0x5b5c81ad, __VMLINUX_SYMBOL_STR(__tty_alloc_driver) },
	{ 0xdad3c1a0, __VMLINUX_SYMBOL_STR(ircomm_control_request) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xf1104ece, __VMLINUX_SYMBOL_STR(iriap_open) },
	{ 0x54496b4, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa29ef45, __VMLINUX_SYMBOL_STR(ircomm_close) },
	{ 0xb8eec15d, __VMLINUX_SYMBOL_STR(tty_kref_put) },
	{ 0x2ca71e02, __VMLINUX_SYMBOL_STR(ircomm_open) },
	{ 0x1a752e48, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0xbfa7c08d, __VMLINUX_SYMBOL_STR(hashbin_lock_find) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x46c1c4a2, __VMLINUX_SYMBOL_STR(irlmp_unregister_service) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x7e67ca6e, __VMLINUX_SYMBOL_STR(irias_new_object) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xf328b42b, __VMLINUX_SYMBOL_STR(tty_port_tty_set) },
	{ 0x38c89d52, __VMLINUX_SYMBOL_STR(ircomm_flow_request) },
	{ 0xe460b3e4, __VMLINUX_SYMBOL_STR(ircomm_data_request) },
	{ 0x36c7321e, __VMLINUX_SYMBOL_STR(tty_port_raise_dtr_rts) },
	{ 0xde4c6b3c, __VMLINUX_SYMBOL_STR(irlmp_service_to_hint) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x15f2be45, __VMLINUX_SYMBOL_STR(tty_wakeup) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x731cec71, __VMLINUX_SYMBOL_STR(hashbin_insert) },
	{ 0x7f52a8bf, __VMLINUX_SYMBOL_STR(irda_param_insert) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=irda,ircomm";


MODULE_INFO(srcversion, "CD8C66A1D283F7D56CDCBEA");
