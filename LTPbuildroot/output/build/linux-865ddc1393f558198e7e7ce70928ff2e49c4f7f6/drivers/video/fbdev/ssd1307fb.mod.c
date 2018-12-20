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
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xb5aebee0, __VMLINUX_SYMBOL_STR(fb_sys_read) },
	{ 0xc22e7785, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x79c26f50, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xf36b5a58, __VMLINUX_SYMBOL_STR(backlight_device_register) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xc9078813, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0xedbd8e13, __VMLINUX_SYMBOL_STR(register_framebuffer) },
	{ 0xd8e15737, __VMLINUX_SYMBOL_STR(pwm_get) },
	{ 0x4dbb4a14, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xa7fe1ea6, __VMLINUX_SYMBOL_STR(gpiod_set_value) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x284bd038, __VMLINUX_SYMBOL_STR(fb_deferred_io_init) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0x90d57597, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0x39e0d40b, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0xcdb71487, __VMLINUX_SYMBOL_STR(devm_regulator_get_optional) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0x9f430854, __VMLINUX_SYMBOL_STR(of_device_get_match_data) },
	{ 0x69d4a5d8, __VMLINUX_SYMBOL_STR(framebuffer_alloc) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x8363da76, __VMLINUX_SYMBOL_STR(sys_fillrect) },
	{ 0x9b031a2b, __VMLINUX_SYMBOL_STR(sys_copyarea) },
	{ 0x7fd8c80d, __VMLINUX_SYMBOL_STR(sys_imageblit) },
	{ 0xae829df1, __VMLINUX_SYMBOL_STR(pwm_apply_state) },
	{ 0xc406d316, __VMLINUX_SYMBOL_STR(framebuffer_release) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xd890fc87, __VMLINUX_SYMBOL_STR(fb_deferred_io_cleanup) },
	{ 0x357ac734, __VMLINUX_SYMBOL_STR(pwm_put) },
	{ 0x3b7598b, __VMLINUX_SYMBOL_STR(unregister_framebuffer) },
	{ 0x18bc49ea, __VMLINUX_SYMBOL_STR(backlight_device_unregister) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xa2141968, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=fb_sys_fops,sysfillrect,syscopyarea,sysimgblt";

MODULE_ALIAS("i2c:ssd1305fb");
MODULE_ALIAS("i2c:ssd1306fb");
MODULE_ALIAS("i2c:ssd1307fb");
MODULE_ALIAS("i2c:ssd1309fb");
MODULE_ALIAS("of:N*T*Csolomon,ssd1305fb-i2c");
MODULE_ALIAS("of:N*T*Csolomon,ssd1305fb-i2cC*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1306fb-i2c");
MODULE_ALIAS("of:N*T*Csolomon,ssd1306fb-i2cC*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1307fb-i2c");
MODULE_ALIAS("of:N*T*Csolomon,ssd1307fb-i2cC*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1309fb-i2c");
MODULE_ALIAS("of:N*T*Csolomon,ssd1309fb-i2cC*");

MODULE_INFO(srcversion, "B627FB5F6A156AF1750F6A4");
