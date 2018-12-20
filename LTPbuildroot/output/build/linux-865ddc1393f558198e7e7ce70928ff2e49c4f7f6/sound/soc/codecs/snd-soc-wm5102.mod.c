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
	{ 0xa2daccc9, __VMLINUX_SYMBOL_STR(arizona_request_irq) },
	{ 0xf3df5ecd, __VMLINUX_SYMBOL_STR(wm_adsp2_event) },
	{ 0x294f2781, __VMLINUX_SYMBOL_STR(arizona_lhpf4_mode) },
	{ 0x962f1aa4, __VMLINUX_SYMBOL_STR(arizona_set_fll) },
	{ 0x13cae825, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0xbd559ac5, __VMLINUX_SYMBOL_STR(arizona_free_spk_irqs) },
	{ 0x91ff1431, __VMLINUX_SYMBOL_STR(arizona_lhpf_coeff_put) },
	{ 0x870156c4, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x227241a5, __VMLINUX_SYMBOL_STR(snd_soc_unregister_platform) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x61b8549e, __VMLINUX_SYMBOL_STR(snd_soc_dapm_get_enum_double) },
	{ 0xc4fa5eb6, __VMLINUX_SYMBOL_STR(arizona_init_dai) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0x3a83f3a5, __VMLINUX_SYMBOL_STR(arizona_in_ev) },
	{ 0x37bcc140, __VMLINUX_SYMBOL_STR(snd_soc_component_disable_pin) },
	{ 0x500f5125, __VMLINUX_SYMBOL_STR(dapm_regulator_event) },
	{ 0x7b770826, __VMLINUX_SYMBOL_STR(arizona_lhpf1_mode) },
	{ 0x729a5ef3, __VMLINUX_SYMBOL_STR(arizona_mixer_values) },
	{ 0x306d8ab3, __VMLINUX_SYMBOL_STR(wm_adsp_compr_set_params) },
	{ 0xd8b84163, __VMLINUX_SYMBOL_STR(snd_soc_add_codec_controls) },
	{ 0x2f87a7a7, __VMLINUX_SYMBOL_STR(regmap_write_async) },
	{ 0x8902435d, __VMLINUX_SYMBOL_STR(arizona_dvfs_down) },
	{ 0xfabedc48, __VMLINUX_SYMBOL_STR(wm_adsp_compr_trigger) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x51a6388e, __VMLINUX_SYMBOL_STR(wm_adsp2_codec_probe) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x174ce453, __VMLINUX_SYMBOL_STR(snd_soc_put_volsw) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0x3057c383, __VMLINUX_SYMBOL_STR(arizona_init_dvfs) },
	{ 0xd1456be8, __VMLINUX_SYMBOL_STR(snd_soc_get_volsw) },
	{ 0xb08d2c49, __VMLINUX_SYMBOL_STR(wm_adsp2_init) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x33d7ff5b, __VMLINUX_SYMBOL_STR(snd_soc_info_enum_double) },
	{ 0x22353d45, __VMLINUX_SYMBOL_STR(wm_adsp2_preloader_get) },
	{ 0xb3a20280, __VMLINUX_SYMBOL_STR(wm_adsp_compr_free) },
	{ 0x9dadd033, __VMLINUX_SYMBOL_STR(arizona_dvfs_up) },
	{ 0xcc875519, __VMLINUX_SYMBOL_STR(wm_adsp2_preloader_put) },
	{ 0xde65fd34, __VMLINUX_SYMBOL_STR(snd_soc_put_volsw_range) },
	{ 0xb89a1b9d, __VMLINUX_SYMBOL_STR(wm_adsp_compr_open) },
	{ 0xbb250271, __VMLINUX_SYMBOL_STR(wm_adsp2_codec_remove) },
	{ 0xc9c29637, __VMLINUX_SYMBOL_STR(arizona_mixer_tlv) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x127f9e71, __VMLINUX_SYMBOL_STR(arizona_out_ev) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x7ad67ab8, __VMLINUX_SYMBOL_STR(arizona_adsp2_rate_controls) },
	{ 0xcfc78cb4, __VMLINUX_SYMBOL_STR(arizona_clk_ev) },
	{ 0x90516841, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw_range) },
	{ 0xdca031b5, __VMLINUX_SYMBOL_STR(snd_soc_bytes_info) },
	{ 0xca77715b, __VMLINUX_SYMBOL_STR(arizona_init_spk) },
	{ 0x9bfe2459, __VMLINUX_SYMBOL_STR(arizona_hp_ev) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x75f49cb9, __VMLINUX_SYMBOL_STR(snd_soc_get_volsw_range) },
	{ 0x44dc9cc8, __VMLINUX_SYMBOL_STR(wm_adsp_compr_copy) },
	{ 0x17f74b1d, __VMLINUX_SYMBOL_STR(arizona_simple_dai_ops) },
	{ 0x62a84e73, __VMLINUX_SYMBOL_STR(wm_adsp_compr_get_caps) },
	{ 0x5ac18032, __VMLINUX_SYMBOL_STR(arizona_free_irq) },
	{ 0x17b5c842, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw) },
	{ 0xece8190f, __VMLINUX_SYMBOL_STR(arizona_lhpf3_mode) },
	{ 0x18c0e2a8, __VMLINUX_SYMBOL_STR(arizona_out_vi_ramp) },
	{ 0x64961f6d, __VMLINUX_SYMBOL_STR(arizona_isrc_fsl) },
	{ 0xcfca551, __VMLINUX_SYMBOL_STR(arizona_in_vi_ramp) },
	{ 0x8835e354, __VMLINUX_SYMBOL_STR(snd_soc_get_enum_double) },
	{ 0xbfb91c11, __VMLINUX_SYMBOL_STR(arizona_dai_ops) },
	{ 0xb0be65, __VMLINUX_SYMBOL_STR(arizona_init_notifiers) },
	{ 0x7f26f273, __VMLINUX_SYMBOL_STR(arizona_mixer_texts) },
	{ 0xce0a30a1, __VMLINUX_SYMBOL_STR(arizona_init_fll) },
	{ 0xd8b9dad3, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x737d3c18, __VMLINUX_SYMBOL_STR(snd_soc_register_platform) },
	{ 0xdb30d7dd, __VMLINUX_SYMBOL_STR(arizona_set_fll_refclk) },
	{ 0x1e3e6de6, __VMLINUX_SYMBOL_STR(snd_soc_unregister_codec) },
	{ 0x65b1a397, __VMLINUX_SYMBOL_STR(arizona_init_gpio) },
	{ 0x600cc139, __VMLINUX_SYMBOL_STR(arizona_dvfs_sysclk_ev) },
	{ 0x79178368, __VMLINUX_SYMBOL_STR(arizona_out_vd_ramp) },
	{ 0x6d2bc491, __VMLINUX_SYMBOL_STR(arizona_in_vd_ramp) },
	{ 0x23a482d9, __VMLINUX_SYMBOL_STR(snd_soc_put_enum_double) },
	{ 0xf7b2b607, __VMLINUX_SYMBOL_STR(arizona_eq_coeff_put) },
	{ 0x966a937b, __VMLINUX_SYMBOL_STR(wm_adsp2_remove) },
	{ 0x2bb57877, __VMLINUX_SYMBOL_STR(snd_soc_bytes_get) },
	{ 0x8e5420e, __VMLINUX_SYMBOL_STR(arizona_set_sysclk) },
	{ 0x576e8d1b, __VMLINUX_SYMBOL_STR(wm_adsp2_early_event) },
	{ 0xa50cbb20, __VMLINUX_SYMBOL_STR(arizona_ng_hold) },
	{ 0xb44ce3d2, __VMLINUX_SYMBOL_STR(snd_soc_new_compress) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xc507102b, __VMLINUX_SYMBOL_STR(snd_soc_bytes_put) },
	{ 0x646c6f87, __VMLINUX_SYMBOL_STR(wm_adsp_compr_handle_irq) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xea07d054, __VMLINUX_SYMBOL_STR(snd_soc_bytes_info_ext) },
	{ 0xfa8d4f6f, __VMLINUX_SYMBOL_STR(snd_soc_register_codec) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x7e3c28d, __VMLINUX_SYMBOL_STR(arizona_init_spk_irqs) },
	{ 0x12496036, __VMLINUX_SYMBOL_STR(wm_adsp_compr_pointer) },
	{ 0x98cd2fc8, __VMLINUX_SYMBOL_STR(snd_soc_dapm_put_enum_double) },
	{ 0x4a9f12bb, __VMLINUX_SYMBOL_STR(arizona_lhpf2_mode) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-wm-adsp,snd-soc-arizona,snd-soc-core";


MODULE_INFO(srcversion, "74E58F0949B03A1FF73BE16");
