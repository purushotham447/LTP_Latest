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
	{ 0xe56a9336, __VMLINUX_SYMBOL_STR(snd_pcm_format_width) },
	{ 0xa2daccc9, __VMLINUX_SYMBOL_STR(arizona_request_irq) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2f04c178, __VMLINUX_SYMBOL_STR(regulator_set_voltage) },
	{ 0xeb711ae7, __VMLINUX_SYMBOL_STR(snd_soc_params_to_bclk) },
	{ 0x815588a6, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0xf28cf8b, __VMLINUX_SYMBOL_STR(snd_soc_dapm_del_routes) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf061815d, __VMLINUX_SYMBOL_STR(regmap_raw_write) },
	{ 0xea124bd1, __VMLINUX_SYMBOL_STR(gcd) },
	{ 0xd500b853, __VMLINUX_SYMBOL_STR(__pm_runtime_suspend) },
	{ 0xbb9df671, __VMLINUX_SYMBOL_STR(snd_soc_dapm_get_volsw) },
	{ 0x1668d406, __VMLINUX_SYMBOL_STR(regmap_multi_reg_write) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0xb6e6d99d, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0x37bcc140, __VMLINUX_SYMBOL_STR(snd_soc_component_disable_pin) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xf4514ade, __VMLINUX_SYMBOL_STR(snd_soc_dapm_new_controls) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xdaa64788, __VMLINUX_SYMBOL_STR(snd_soc_component_enable_pin) },
	{ 0x33d7ff5b, __VMLINUX_SYMBOL_STR(snd_soc_info_enum_double) },
	{ 0x79a2a8f0, __VMLINUX_SYMBOL_STR(snd_soc_dapm_add_routes) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x8428cb8a, __VMLINUX_SYMBOL_STR(snd_soc_read) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb59aba19, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_list) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xeb9461ea, __VMLINUX_SYMBOL_STR(snd_soc_update_bits) },
	{ 0x568be9b1, __VMLINUX_SYMBOL_STR(dev_crit) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x75682149, __VMLINUX_SYMBOL_STR(snd_soc_dapm_put_volsw) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x5ac18032, __VMLINUX_SYMBOL_STR(arizona_free_irq) },
	{ 0x17b5c842, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw) },
	{ 0x8835e354, __VMLINUX_SYMBOL_STR(snd_soc_get_enum_double) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x7c9a7371, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xe850c660, __VMLINUX_SYMBOL_STR(snd_soc_dapm_sync) },
	{ 0x23a482d9, __VMLINUX_SYMBOL_STR(snd_soc_put_enum_double) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xc507102b, __VMLINUX_SYMBOL_STR(snd_soc_bytes_put) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x24f4a8ff, __VMLINUX_SYMBOL_STR(regmap_get_val_bytes) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0xc7c5b76f, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0x897fa0e5, __VMLINUX_SYMBOL_STR(snd_soc_write) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-pcm,snd-soc-core";


MODULE_INFO(srcversion, "E0D0A3D4A58F53AA224BAF8");
