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
	{ 0xa34ef983, __VMLINUX_SYMBOL_STR(drm_gem_cma_vm_ops) },
	{ 0x6d30c675, __VMLINUX_SYMBOL_STR(drm_gem_cma_dumb_create) },
	{ 0xd635e176, __VMLINUX_SYMBOL_STR(drm_gem_cma_prime_mmap) },
	{ 0x6cbb2b17, __VMLINUX_SYMBOL_STR(drm_gem_cma_prime_vunmap) },
	{ 0x4be5b4f6, __VMLINUX_SYMBOL_STR(drm_gem_cma_prime_vmap) },
	{ 0x385cf09e, __VMLINUX_SYMBOL_STR(tinydrm_gem_cma_prime_import_sg_table) },
	{ 0xe98da046, __VMLINUX_SYMBOL_STR(drm_gem_cma_prime_get_sg_table) },
	{ 0x410562, __VMLINUX_SYMBOL_STR(drm_gem_prime_import) },
	{ 0x2d0fabd5, __VMLINUX_SYMBOL_STR(drm_gem_prime_export) },
	{ 0x2b4388ae, __VMLINUX_SYMBOL_STR(drm_gem_prime_fd_to_handle) },
	{ 0xa08b687b, __VMLINUX_SYMBOL_STR(drm_gem_prime_handle_to_fd) },
	{ 0x60b2e793, __VMLINUX_SYMBOL_STR(tinydrm_gem_cma_free_object) },
	{ 0x40023d4, __VMLINUX_SYMBOL_STR(drm_release) },
	{ 0x3ff04dd5, __VMLINUX_SYMBOL_STR(drm_open) },
	{ 0xec31530f, __VMLINUX_SYMBOL_STR(drm_gem_cma_mmap) },
	{ 0xae6c4ed1, __VMLINUX_SYMBOL_STR(drm_ioctl) },
	{ 0x6c462fcc, __VMLINUX_SYMBOL_STR(drm_poll) },
	{ 0x70852c83, __VMLINUX_SYMBOL_STR(drm_read) },
	{ 0xcba1c24c, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x55f91c5e, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_prepare_fb) },
	{ 0x89e3add4, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_update) },
	{ 0xbb34612b, __VMLINUX_SYMBOL_STR(drm_fb_cma_create_handle) },
	{ 0xee4f1eed, __VMLINUX_SYMBOL_STR(drm_fb_cma_destroy) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x7bd5aecd, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0x45bf34ac, __VMLINUX_SYMBOL_STR(gpiod_get_value_cansleep) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x552bd7cc, __VMLINUX_SYMBOL_STR(dma_buf_end_cpu_access) },
	{ 0x18cd8a17, __VMLINUX_SYMBOL_STR(tinydrm_xrgb8888_to_gray8) },
	{ 0x4b67cea, __VMLINUX_SYMBOL_STR(dma_buf_begin_cpu_access) },
	{ 0x7eb31bfa, __VMLINUX_SYMBOL_STR(thermal_zone_get_temp) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xd03b80c0, __VMLINUX_SYMBOL_STR(drm_fb_cma_get_gem_obj) },
	{ 0x3a26ed11, __VMLINUX_SYMBOL_STR(sched_clock) },
	{ 0xc35c284f, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0x43c91d37, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0xf3207539, __VMLINUX_SYMBOL_STR(drm_printk) },
	{ 0x3544ac73, __VMLINUX_SYMBOL_STR(devm_tinydrm_register) },
	{ 0xdd82fa2c, __VMLINUX_SYMBOL_STR(drm_mode_config_reset) },
	{ 0xcf03d8b9, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_init) },
	{ 0xd8c0879c, __VMLINUX_SYMBOL_STR(devm_tinydrm_init) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xa7fba05b, __VMLINUX_SYMBOL_STR(thermal_zone_get_zone_by_name) },
	{ 0x75a8204c, __VMLINUX_SYMBOL_STR(device_property_read_string) },
	{ 0x4b506a36, __VMLINUX_SYMBOL_STR(devm_gpiod_get) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x809e3303, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa4714371, __VMLINUX_SYMBOL_STR(tinydrm_shutdown) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm,tinydrm,drm_kms_helper";

MODULE_ALIAS("spi:e1144cs021");
MODULE_ALIAS("spi:e1190cs021");
MODULE_ALIAS("spi:e2200cs021");
MODULE_ALIAS("spi:e2271cs021");
MODULE_ALIAS("of:N*T*Cpervasive,e1144cs021");
MODULE_ALIAS("of:N*T*Cpervasive,e1144cs021C*");
MODULE_ALIAS("of:N*T*Cpervasive,e1190cs021");
MODULE_ALIAS("of:N*T*Cpervasive,e1190cs021C*");
MODULE_ALIAS("of:N*T*Cpervasive,e2200cs021");
MODULE_ALIAS("of:N*T*Cpervasive,e2200cs021C*");
MODULE_ALIAS("of:N*T*Cpervasive,e2271cs021");
MODULE_ALIAS("of:N*T*Cpervasive,e2271cs021C*");

MODULE_INFO(srcversion, "327BE4B1746881E56F1F543");
