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
	{ 0x9dcedde5, __VMLINUX_SYMBOL_STR(mipi_dbi_debugfs_init) },
	{ 0x1e17a9f3, __VMLINUX_SYMBOL_STR(tinydrm_lastclose) },
	{ 0x40023d4, __VMLINUX_SYMBOL_STR(drm_release) },
	{ 0x3ff04dd5, __VMLINUX_SYMBOL_STR(drm_open) },
	{ 0xec31530f, __VMLINUX_SYMBOL_STR(drm_gem_cma_mmap) },
	{ 0xae6c4ed1, __VMLINUX_SYMBOL_STR(drm_ioctl) },
	{ 0x6c462fcc, __VMLINUX_SYMBOL_STR(drm_poll) },
	{ 0x70852c83, __VMLINUX_SYMBOL_STR(drm_read) },
	{ 0xcba1c24c, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x55f91c5e, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_prepare_fb) },
	{ 0x89e3add4, __VMLINUX_SYMBOL_STR(tinydrm_display_pipe_update) },
	{ 0xd4bc8453, __VMLINUX_SYMBOL_STR(mipi_dbi_pipe_disable) },
	{ 0xea45cb3f, __VMLINUX_SYMBOL_STR(mipi_dbi_pipe_enable) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x7bd5aecd, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x4024d4de, __VMLINUX_SYMBOL_STR(mipi_dbi_command_buf) },
	{ 0xcf676216, __VMLINUX_SYMBOL_STR(mipi_dbi_hw_reset) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x3544ac73, __VMLINUX_SYMBOL_STR(devm_tinydrm_register) },
	{ 0x232c1746, __VMLINUX_SYMBOL_STR(devm_add_action) },
	{ 0x99aeee46, __VMLINUX_SYMBOL_STR(mipi_dbi_display_is_on) },
	{ 0x4dbb4a14, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0x98f16ff4, __VMLINUX_SYMBOL_STR(mipi_dbi_init) },
	{ 0x40260b04, __VMLINUX_SYMBOL_STR(mipi_dbi_spi_init) },
	{ 0x1cda20a2, __VMLINUX_SYMBOL_STR(device_property_read_u32_array) },
	{ 0xaeac1ec9, __VMLINUX_SYMBOL_STR(tinydrm_of_find_backlight) },
	{ 0xc9b9eb52, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xc9078813, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0xf3207539, __VMLINUX_SYMBOL_STR(drm_printk) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa4714371, __VMLINUX_SYMBOL_STR(tinydrm_shutdown) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm,tinydrm,mipi-dbi";

MODULE_ALIAS("spi:mi0283qt");
MODULE_ALIAS("of:N*T*Cmulti-inno,mi0283qt");
MODULE_ALIAS("of:N*T*Cmulti-inno,mi0283qtC*");

MODULE_INFO(srcversion, "89DEB5ED8ECD0827F362CC0");
