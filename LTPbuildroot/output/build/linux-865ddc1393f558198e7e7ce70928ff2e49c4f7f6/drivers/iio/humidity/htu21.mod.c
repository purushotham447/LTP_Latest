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
	{ 0x3a73babd, __VMLINUX_SYMBOL_STR(ms_sensors_show_battery_low) },
	{ 0x9d169f26, __VMLINUX_SYMBOL_STR(ms_sensors_show_heater) },
	{ 0xd64397eb, __VMLINUX_SYMBOL_STR(ms_sensors_write_heater) },
	{ 0xc1ff3221, __VMLINUX_SYMBOL_STR(ms_sensors_ht_read_temperature) },
	{ 0x7e22b90c, __VMLINUX_SYMBOL_STR(ms_sensors_ht_read_humidity) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xb67f4c8a, __VMLINUX_SYMBOL_STR(ms_sensors_write_resolution) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xfb807d84, __VMLINUX_SYMBOL_STR(devm_iio_device_register) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x23d108ff, __VMLINUX_SYMBOL_STR(ms_sensors_read_serial) },
	{ 0xc77b421f, __VMLINUX_SYMBOL_STR(ms_sensors_reset) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xd892e08d, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,ms_sensors_i2c";

MODULE_ALIAS("of:N*T*Cmeas,htu21");
MODULE_ALIAS("of:N*T*Cmeas,htu21C*");
MODULE_ALIAS("of:N*T*Cmeas,ms8607-humidity");
MODULE_ALIAS("of:N*T*Cmeas,ms8607-humidityC*");
MODULE_ALIAS("i2c:htu21");
MODULE_ALIAS("i2c:ms8607-humidity");

MODULE_INFO(srcversion, "214B34E3576C203E51A93C3");
