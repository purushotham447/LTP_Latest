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
	{ 0x552dced5, __VMLINUX_SYMBOL_STR(mipi_dsi_driver_unregister) },
	{ 0x84e12845, __VMLINUX_SYMBOL_STR(mipi_dsi_driver_register_full) },
	{ 0xda7c0bcf, __VMLINUX_SYMBOL_STR(mipi_dsi_attach) },
	{ 0xbc6cda7, __VMLINUX_SYMBOL_STR(drm_panel_add) },
	{ 0x17cd620d, __VMLINUX_SYMBOL_STR(drm_panel_init) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x3672e466, __VMLINUX_SYMBOL_STR(of_find_i2c_device_by_node) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xb457fc69, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0xc197bf4c, __VMLINUX_SYMBOL_STR(drm_mode_probed_add) },
	{ 0xbe0e636d, __VMLINUX_SYMBOL_STR(drm_mode_set_name) },
	{ 0xd20f60d2, __VMLINUX_SYMBOL_STR(drm_mode_duplicate) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x83db54a5, __VMLINUX_SYMBOL_STR(drm_panel_remove) },
	{ 0x20938f59, __VMLINUX_SYMBOL_STR(drm_panel_detach) },
	{ 0xf935cb84, __VMLINUX_SYMBOL_STR(mipi_dsi_detach) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf58acbdf, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm";

MODULE_ALIAS("of:N*T*Craspberrypi,touchscreen");
MODULE_ALIAS("of:N*T*Craspberrypi,touchscreenC*");

MODULE_INFO(srcversion, "93911506D0FD6586963F8B1");
