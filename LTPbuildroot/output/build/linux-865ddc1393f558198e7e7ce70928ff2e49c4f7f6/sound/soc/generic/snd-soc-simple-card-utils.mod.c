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
	{ 0xb077e70a, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x815588a6, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0x2f7cc1fa, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_card_name) },
	{ 0x92697151, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_audio_simple_widgets) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb6e6d99d, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x556e4390, __VMLINUX_SYMBOL_STR(clk_get_rate) },
	{ 0x7ed05250, __VMLINUX_SYMBOL_STR(of_graph_get_port_parent) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x71df34c1, __VMLINUX_SYMBOL_STR(snd_soc_of_get_dai_name) },
	{ 0x2f830e9b, __VMLINUX_SYMBOL_STR(of_graph_get_next_endpoint) },
	{ 0x90d57597, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0xd960dac9, __VMLINUX_SYMBOL_STR(devm_get_clk_from_child) },
	{ 0x6b7dceb1, __VMLINUX_SYMBOL_STR(of_graph_get_endpoint_count) },
	{ 0x7c9a7371, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xae28b2a6, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_sysclk) },
	{ 0x2951e8a8, __VMLINUX_SYMBOL_STR(devm_kvasprintf) },
	{ 0xe2292689, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_audio_routing) },
	{ 0xa611a494, __VMLINUX_SYMBOL_STR(snd_soc_get_dai_id) },
	{ 0x2d18c35e, __VMLINUX_SYMBOL_STR(snd_soc_get_dai_name) },
	{ 0x6dc6b5e8, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_daifmt) },
	{ 0xcfde09c3, __VMLINUX_SYMBOL_STR(of_parse_phandle_with_args) },
	{ 0x25bac302, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_tdm_slot) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x39e0d40b, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core";


MODULE_INFO(srcversion, "1AC4BF04FC0CDD63620A99A");
