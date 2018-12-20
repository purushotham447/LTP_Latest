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
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x56454062, __VMLINUX_SYMBOL_STR(power_supply_register) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x39e0d40b, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0x9f430854, __VMLINUX_SYMBOL_STR(of_device_get_match_data) },
	{ 0x1cb3d3ac, __VMLINUX_SYMBOL_STR(of_node_get) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x58d2273e, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x36b04e13, __VMLINUX_SYMBOL_STR(power_supply_changed) },
	{ 0x7990026b, __VMLINUX_SYMBOL_STR(power_supply_get_drvdata) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xfe043f32, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xad99b748, __VMLINUX_SYMBOL_STR(i2c_smbus_write_i2c_block_data) },
	{ 0x440b81, __VMLINUX_SYMBOL_STR(power_supply_unregister) },
	{ 0x625e6bc, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Clltc,ltc2941");
MODULE_ALIAS("of:N*T*Clltc,ltc2941C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2942");
MODULE_ALIAS("of:N*T*Clltc,ltc2942C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2943");
MODULE_ALIAS("of:N*T*Clltc,ltc2943C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2944");
MODULE_ALIAS("of:N*T*Clltc,ltc2944C*");
MODULE_ALIAS("i2c:ltc2941");
MODULE_ALIAS("i2c:ltc2942");
MODULE_ALIAS("i2c:ltc2943");
MODULE_ALIAS("i2c:ltc2944");

MODULE_INFO(srcversion, "19451663E17021FE350E86D");
