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
	{ 0xa91f3544, __VMLINUX_SYMBOL_STR(regulator_get_bypass_regmap) },
	{ 0x2f9b6602, __VMLINUX_SYMBOL_STR(regulator_is_enabled_regmap) },
	{ 0xa768ba5c, __VMLINUX_SYMBOL_STR(regulator_get_voltage_sel_regmap) },
	{ 0xf1c2dfd, __VMLINUX_SYMBOL_STR(regulator_set_voltage_sel_regmap) },
	{ 0x637d1003, __VMLINUX_SYMBOL_STR(regulator_map_voltage_linear_range) },
	{ 0xead4d75a, __VMLINUX_SYMBOL_STR(regulator_list_voltage_linear_range) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x667d292, __VMLINUX_SYMBOL_STR(of_get_regulator_init_data) },
	{ 0x67c63256, __VMLINUX_SYMBOL_STR(of_get_child_by_name) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x8eecc688, __VMLINUX_SYMBOL_STR(devm_regulator_register) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xf842b6b4, __VMLINUX_SYMBOL_STR(snd_soc_component_force_enable_pin) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe850c660, __VMLINUX_SYMBOL_STR(snd_soc_dapm_sync) },
	{ 0x37bcc140, __VMLINUX_SYMBOL_STR(snd_soc_component_disable_pin) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0x771c1d97, __VMLINUX_SYMBOL_STR(regulator_enable_regmap) },
	{ 0x23282b9d, __VMLINUX_SYMBOL_STR(regulator_disable_regmap) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x6eda372, __VMLINUX_SYMBOL_STR(regulator_set_bypass_regmap) },
	{ 0xfe1c667c, __VMLINUX_SYMBOL_STR(rdev_get_drvdata) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core";


MODULE_INFO(srcversion, "CB43FC7DFF11ECADBACDC40");
