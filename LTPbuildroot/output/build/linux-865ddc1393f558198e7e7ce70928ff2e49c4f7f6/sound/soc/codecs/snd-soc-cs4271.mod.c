#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0xbaeef7b0, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x174ce453, __VMLINUX_SYMBOL_STR(snd_soc_put_volsw) },
	{ 0xd1456be8, __VMLINUX_SYMBOL_STR(snd_soc_get_volsw) },
	{ 0x71f499f6, __VMLINUX_SYMBOL_STR(devm_regulator_bulk_get) },
	{ 0x3a6f0594, __VMLINUX_SYMBOL_STR(regulator_bulk_enable) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x5be5f04e, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x809e3303, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0xe5f05970, __VMLINUX_SYMBOL_STR(snd_ctl_boolean_mono_info) },
	{ 0x17b5c842, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw) },
	{ 0x9a83d378, __VMLINUX_SYMBOL_STR(regulator_bulk_disable) },
	{ 0xaae6c7b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xa6d1a808, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0x134165c, __VMLINUX_SYMBOL_STR(regcache_mark_dirty) },
	{ 0x9ca0b1e0, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0xfa8d4f6f, __VMLINUX_SYMBOL_STR(snd_soc_register_codec) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xf9a59a10, __VMLINUX_SYMBOL_STR(devm_gpio_request) },
	{ 0xc293114f, __VMLINUX_SYMBOL_STR(regcache_sync) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core,snd";

MODULE_ALIAS("of:N*T*Ccirrus,cs4271");
MODULE_ALIAS("of:N*T*Ccirrus,cs4271C*");

MODULE_INFO(srcversion, "420B1F407622D8F702E988C");
