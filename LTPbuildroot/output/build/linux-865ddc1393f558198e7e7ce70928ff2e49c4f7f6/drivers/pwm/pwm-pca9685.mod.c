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
	{ 0xc22e7785, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x79c26f50, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xd8b9dad3, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x12bde086, __VMLINUX_SYMBOL_STR(__pm_runtime_set_status) },
	{ 0xf6ddb523, __VMLINUX_SYMBOL_STR(devm_gpiochip_add_data) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x6d96ec50, __VMLINUX_SYMBOL_STR(pwmchip_add) },
	{ 0x7fd3db2d, __VMLINUX_SYMBOL_STR(device_property_present) },
	{ 0x7cae589a, __VMLINUX_SYMBOL_STR(__devm_regmap_init_i2c) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x3c5d72, __VMLINUX_SYMBOL_STR(pwm_set_chip_data) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0x2d829396, __VMLINUX_SYMBOL_STR(gpiochip_get_data) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xbf0d9a24, __VMLINUX_SYMBOL_STR(pwm_get_chip_data) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x72451e7, __VMLINUX_SYMBOL_STR(gpiochip_is_requested) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x13cae825, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0x870156c4, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x323fc90f, __VMLINUX_SYMBOL_STR(pwmchip_remove) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cnxp,pca9685-pwm");
MODULE_ALIAS("of:N*T*Cnxp,pca9685-pwmC*");
MODULE_ALIAS("i2c:pca9685");

MODULE_INFO(srcversion, "67184518A46221F146DB6A7");
