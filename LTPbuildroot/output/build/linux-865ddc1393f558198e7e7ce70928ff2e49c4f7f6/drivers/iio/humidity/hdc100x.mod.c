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
	{ 0xfa88cd00, __VMLINUX_SYMBOL_STR(iio_read_const_attr) },
	{ 0xc22e7785, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x79c26f50, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x402e31ac, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x853bd37, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xd892e08d, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x5d03e104, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0x6c6ae64a, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0x1418c233, __VMLINUX_SYMBOL_STR(i2c_smbus_write_word_data) },
	{ 0x9e15e1b1, __VMLINUX_SYMBOL_STR(iio_device_release_direct_mode) },
	{ 0x22bf802c, __VMLINUX_SYMBOL_STR(iio_device_claim_direct_mode) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x16f3e04c, __VMLINUX_SYMBOL_STR(iio_trigger_notify_done) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xbf54a7d6, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0xeda7dbf7, __VMLINUX_SYMBOL_STR(iio_get_time_ns) },
	{ 0xee9f6461, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x8eece50b, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2d87b81a, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0xa7908474, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,industrialio-triggered-buffer";

MODULE_ALIAS("of:N*T*Cti,hdc1000");
MODULE_ALIAS("of:N*T*Cti,hdc1000C*");
MODULE_ALIAS("of:N*T*Cti,hdc1008");
MODULE_ALIAS("of:N*T*Cti,hdc1008C*");
MODULE_ALIAS("of:N*T*Cti,hdc1010");
MODULE_ALIAS("of:N*T*Cti,hdc1010C*");
MODULE_ALIAS("of:N*T*Cti,hdc1050");
MODULE_ALIAS("of:N*T*Cti,hdc1050C*");
MODULE_ALIAS("of:N*T*Cti,hdc1080");
MODULE_ALIAS("of:N*T*Cti,hdc1080C*");
MODULE_ALIAS("i2c:hdc100x");
MODULE_ALIAS("i2c:hdc1000");
MODULE_ALIAS("i2c:hdc1008");
MODULE_ALIAS("i2c:hdc1010");
MODULE_ALIAS("i2c:hdc1050");
MODULE_ALIAS("i2c:hdc1080");

MODULE_INFO(srcversion, "9E0A525BC9178715C77FF31");
