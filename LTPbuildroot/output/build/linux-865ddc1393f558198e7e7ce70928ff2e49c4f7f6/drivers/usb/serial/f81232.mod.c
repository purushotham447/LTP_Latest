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
	{ 0x8bb2128f, __VMLINUX_SYMBOL_STR(usb_serial_generic_tiocmiwait) },
	{ 0xf60f5f80, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x9da3d378, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0x2705f125, __VMLINUX_SYMBOL_STR(usb_serial_generic_open) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x653e8626, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xb1c8d2f1, __VMLINUX_SYMBOL_STR(usb_serial_generic_close) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd09422d5, __VMLINUX_SYMBOL_STR(tty_encode_baud_rate) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0xf2997713, __VMLINUX_SYMBOL_STR(tty_termios_hw_change) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xb8eec15d, __VMLINUX_SYMBOL_STR(tty_kref_put) },
	{ 0x5b46a06f, __VMLINUX_SYMBOL_STR(usb_serial_handle_dcd_change) },
	{ 0xf4a5be32, __VMLINUX_SYMBOL_STR(tty_port_tty_get) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x26f02757, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x1a752e48, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x1c06bcf1, __VMLINUX_SYMBOL_STR(usb_serial_handle_break) },
	{ 0x2eee0e10, __VMLINUX_SYMBOL_STR(usb_serial_handle_sysrq_char) },
	{ 0x56d44447, __VMLINUX_SYMBOL_STR(__tty_insert_flip_char) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v1934p0706d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "42B2FD15BB0B041DFDC45EA");
