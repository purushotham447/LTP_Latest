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
	{ 0x6922d1fe, __VMLINUX_SYMBOL_STR(of_find_backlight_by_node) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x26cb2d19, __VMLINUX_SYMBOL_STR(drm_dev_register) },
	{ 0x308b6354, __VMLINUX_SYMBOL_STR(drm_atomic_helper_suspend) },
	{ 0x5acfe4eb, __VMLINUX_SYMBOL_STR(drm_dev_alloc) },
	{ 0xd89f74b1, __VMLINUX_SYMBOL_STR(drm_fbdev_cma_init_with_funcs) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x66bb51c5, __VMLINUX_SYMBOL_STR(drm_atomic_helper_resume) },
	{ 0x684525a9, __VMLINUX_SYMBOL_STR(drm_fbdev_cma_set_suspend_unlocked) },
	{ 0xff0ff108, __VMLINUX_SYMBOL_STR(drm_mode_config_cleanup) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x1615c6ef, __VMLINUX_SYMBOL_STR(drm_atomic_helper_connector_reset) },
	{ 0xba0eecd2, __VMLINUX_SYMBOL_STR(drm_fb_cma_prepare_fb) },
	{ 0x39943bbc, __VMLINUX_SYMBOL_STR(drm_helper_probe_single_connector_modes) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x1be0b645, __VMLINUX_SYMBOL_STR(drm_dev_unref) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x9f4c144d, __VMLINUX_SYMBOL_STR(drm_connector_cleanup) },
	{ 0x29d0d9b9, __VMLINUX_SYMBOL_STR(drm_simple_display_pipe_init) },
	{ 0xde953868, __VMLINUX_SYMBOL_STR(drm_atomic_helper_connector_duplicate_state) },
	{ 0xd40e40b9, __VMLINUX_SYMBOL_STR(dma_buf_vunmap) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x79611bff, __VMLINUX_SYMBOL_STR(drm_dev_unregister) },
	{ 0xcc337fd5, __VMLINUX_SYMBOL_STR(drm_fbdev_cma_restore_mode) },
	{ 0xc46f41c5, __VMLINUX_SYMBOL_STR(drm_fb_cma_create_with_funcs) },
	{ 0xbe0e636d, __VMLINUX_SYMBOL_STR(drm_mode_set_name) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd20f60d2, __VMLINUX_SYMBOL_STR(drm_mode_duplicate) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x165c30f8, __VMLINUX_SYMBOL_STR(drm_connector_init) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0x232c1746, __VMLINUX_SYMBOL_STR(devm_add_action) },
	{ 0xf3207539, __VMLINUX_SYMBOL_STR(drm_printk) },
	{ 0x1cf63a16, __VMLINUX_SYMBOL_STR(drm_atomic_helper_connector_destroy_state) },
	{ 0xc2acc033, __VMLINUX_SYMBOL_STR(hex_dump_to_buffer) },
	{ 0xf2fc5827, __VMLINUX_SYMBOL_STR(drm_atomic_helper_check) },
	{ 0x93eb4949, __VMLINUX_SYMBOL_STR(drm_atomic_helper_commit) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x30b35608, __VMLINUX_SYMBOL_STR(drm_crtc_send_vblank_event) },
	{ 0x3b9d009a, __VMLINUX_SYMBOL_STR(drm_format_plane_cpp) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xed9aa8da, __VMLINUX_SYMBOL_STR(drm_gem_cma_prime_import_sg_table) },
	{ 0x47f0165a, __VMLINUX_SYMBOL_STR(drm_mode_config_init) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x91cb02f0, __VMLINUX_SYMBOL_STR(drm_atomic_helper_shutdown) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xc197bf4c, __VMLINUX_SYMBOL_STR(drm_mode_probed_add) },
	{ 0x1148b623, __VMLINUX_SYMBOL_STR(drm_fbdev_cma_fini) },
	{ 0x8a4e9e5a, __VMLINUX_SYMBOL_STR(drm_gem_cma_free_object) },
	{ 0xbdbbb475, __VMLINUX_SYMBOL_STR(dma_buf_vmap) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x89a596db, __VMLINUX_SYMBOL_STR(drm_atomic_helper_best_encoder) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm,drm_kms_helper";


MODULE_INFO(srcversion, "E5EACFCCF53B10E31260020");
