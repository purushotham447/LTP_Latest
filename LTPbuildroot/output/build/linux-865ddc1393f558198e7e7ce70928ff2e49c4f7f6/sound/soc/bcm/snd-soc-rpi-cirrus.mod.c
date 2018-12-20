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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x61b8549e, __VMLINUX_SYMBOL_STR(snd_soc_dapm_get_enum_double) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0xdd106233, __VMLINUX_SYMBOL_STR(snd_soc_codec_set_sysclk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe9559f77, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_pll) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x33d7ff5b, __VMLINUX_SYMBOL_STR(snd_soc_info_enum_double) },
	{ 0x8428cb8a, __VMLINUX_SYMBOL_STR(snd_soc_read) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xeb9461ea, __VMLINUX_SYMBOL_STR(snd_soc_update_bits) },
	{ 0x6285c762, __VMLINUX_SYMBOL_STR(snd_soc_codec_set_pll) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe5f05970, __VMLINUX_SYMBOL_STR(snd_ctl_boolean_mono_info) },
	{ 0x54bbb4c3, __VMLINUX_SYMBOL_STR(snd_soc_get_pcm_runtime) },
	{ 0xdb6fe13, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_bclk_ratio) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x5f21c7c, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_clkdiv) },
	{ 0xae28b2a6, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_sysclk) },
	{ 0x68a24153, __VMLINUX_SYMBOL_STR(snd_pcm_format_physical_width) },
	{ 0x81fc8a11, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_minmax) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x25bac302, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_tdm_slot) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x98cd2fc8, __VMLINUX_SYMBOL_STR(snd_soc_dapm_put_enum_double) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core,snd,snd-pcm";

MODULE_ALIAS("of:N*T*Cwlf,rpi-cirrus");
MODULE_ALIAS("of:N*T*Cwlf,rpi-cirrusC*");

MODULE_INFO(srcversion, "8D6F95864705FF5090C0C9D");
