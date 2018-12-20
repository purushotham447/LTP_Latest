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
	{ 0x60cbff9f, __VMLINUX_SYMBOL_STR(devm_snd_soc_register_card) },
	{ 0x14531ef1, __VMLINUX_SYMBOL_STR(asoc_simple_card_canonicalize_dailink) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x92e40e41, __VMLINUX_SYMBOL_STR(asoc_simple_card_canonicalize_cpu) },
	{ 0x2db02a3c, __VMLINUX_SYMBOL_STR(of_phandle_iterator_init) },
	{ 0x3f214723, __VMLINUX_SYMBOL_STR(asoc_simple_card_clean_reference) },
	{ 0x7edf479d, __VMLINUX_SYMBOL_STR(snd_soc_pm_ops) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x3a7cbf52, __VMLINUX_SYMBOL_STR(asoc_simple_card_parse_graph_dai) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x76a0724, __VMLINUX_SYMBOL_STR(asoc_simple_card_clk_enable) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe8b99712, __VMLINUX_SYMBOL_STR(asoc_simple_card_clk_disable) },
	{ 0x723a68b8, __VMLINUX_SYMBOL_STR(asoc_simple_card_of_parse_widgets) },
	{ 0x84fd911e, __VMLINUX_SYMBOL_STR(asoc_simple_card_set_dailink_name) },
	{ 0xc0e517a0, __VMLINUX_SYMBOL_STR(asoc_simple_card_of_parse_routing) },
	{ 0x6b7dceb1, __VMLINUX_SYMBOL_STR(of_graph_get_endpoint_count) },
	{ 0x92ac0ecd, __VMLINUX_SYMBOL_STR(asoc_simple_card_init_dai) },
	{ 0x653a6c5d, __VMLINUX_SYMBOL_STR(asoc_simple_card_parse_clk) },
	{ 0x31605819, __VMLINUX_SYMBOL_STR(asoc_simple_card_parse_daifmt) },
	{ 0x4cca29e0, __VMLINUX_SYMBOL_STR(of_get_next_child) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0x39a25f4e, __VMLINUX_SYMBOL_STR(of_phandle_iterator_next) },
	{ 0xc2d7a170, __VMLINUX_SYMBOL_STR(asoc_simple_card_parse_card_name) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xdc864e2b, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_tdm_slot) },
	{ 0xed8758bf, __VMLINUX_SYMBOL_STR(of_graph_get_remote_endpoint) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core,snd-soc-simple-card-utils";

MODULE_ALIAS("of:N*T*Caudio-graph-card");
MODULE_ALIAS("of:N*T*Caudio-graph-cardC*");

MODULE_INFO(srcversion, "11559119FF1E92B6308834B");
