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
	{ 0x48bf23bc, __VMLINUX_SYMBOL_STR(tinydrm_swab16) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xee4f1eed, __VMLINUX_SYMBOL_STR(drm_fb_cma_destroy) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x59a3406, __VMLINUX_SYMBOL_STR(tinydrm_xrgb8888_to_rgb565) },
	{ 0xdd82fa2c, __VMLINUX_SYMBOL_STR(drm_mode_config_reset) },
	{ 0x43c91d37, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x7b6e6972, __VMLINUX_SYMBOL_STR(tinydrm_spi_max_transfer_size) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xd8c0879c, __VMLINUX_SYMBOL_STR(devm_tinydrm_init) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x97106714, __VMLINUX_SYMBOL_STR(memdup_user_nul) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0xca801cdc, __VMLINUX_SYMBOL_STR(tinydrm_spi_transfer) },
	{ 0x2c346f30, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x36e0fb3, __VMLINUX_SYMBOL_STR(drm_fb_cma_debugfs_show) },
	{ 0xb8b2395e, __VMLINUX_SYMBOL_STR(tinydrm_disable_backlight) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x5a5a94a6, __VMLINUX_SYMBOL_STR(kstrtou8) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xfa5935b2, __VMLINUX_SYMBOL_STR(tinydrm_merge_clips) },
	{ 0xd03b80c0, __VMLINUX_SYMBOL_STR(drm_fb_cma_get_gem_obj) },
	{ 0xcb1e6028, __VMLINUX_SYMBOL_STR(tinydrm_spi_bpw_supported) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x422702f6, __VMLINUX_SYMBOL_STR(drm_debugfs_create_files) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0x4b67cea, __VMLINUX_SYMBOL_STR(dma_buf_begin_cpu_access) },
	{ 0xf3207539, __VMLINUX_SYMBOL_STR(drm_printk) },
	{ 0x3cc1b6d7, __VMLINUX_SYMBOL_STR(tinydrm_memcpy) },
	{ 0xcf03d8b9, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_init) },
	{ 0xbb34612b, __VMLINUX_SYMBOL_STR(drm_fb_cma_create_handle) },
	{ 0xe4dc77b2, __VMLINUX_SYMBOL_STR(drm_get_format_name) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x552bd7cc, __VMLINUX_SYMBOL_STR(dma_buf_end_cpu_access) },
	{ 0xb801693e, __VMLINUX_SYMBOL_STR(tinydrm_enable_backlight) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tinydrm,drm_kms_helper,drm";


MODULE_INFO(srcversion, "BA13CC01576B7F8130030C7");
