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
	{ 0xe56a9336, __VMLINUX_SYMBOL_STR(snd_pcm_format_width) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc9078813, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0x53817baa, __VMLINUX_SYMBOL_STR(regcache_cache_bypass) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xf4514ade, __VMLINUX_SYMBOL_STR(snd_soc_dapm_new_controls) },
	{ 0x174ce453, __VMLINUX_SYMBOL_STR(snd_soc_put_volsw) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xd1456be8, __VMLINUX_SYMBOL_STR(snd_soc_get_volsw) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xa3209eb0, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_mask64) },
	{ 0xb59aba19, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_list) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x17b5c842, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw) },
	{ 0xc9b9eb52, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0xcdb71487, __VMLINUX_SYMBOL_STR(devm_regulator_get_optional) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0x134165c, __VMLINUX_SYMBOL_STR(regcache_mark_dirty) },
	{ 0x81fc8a11, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_minmax) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0xfa8d4f6f, __VMLINUX_SYMBOL_STR(snd_soc_register_codec) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0xc293114f, __VMLINUX_SYMBOL_STR(regcache_sync) },
	{ 0xd08c099f, __VMLINUX_SYMBOL_STR(regcache_cache_only) },
	{ 0x4dbb4a14, __VMLINUX_SYMBOL_STR(regulator_enable) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-pcm,snd-soc-core";


MODULE_INFO(srcversion, "5F72D803407BBB9723E1944");
