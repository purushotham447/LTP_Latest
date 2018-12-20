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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe18754ca, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x9c74279b, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x66e2e466, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x7bd5aecd, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0x8ebf2429, __VMLINUX_SYMBOL_STR(fbtft_unregister_framebuffer) },
	{ 0xc2a975ff, __VMLINUX_SYMBOL_STR(fbtft_write_spi_emulate_9) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xc21b8236, __VMLINUX_SYMBOL_STR(fbtft_write_gpio8_wr) },
	{ 0xa2b9c130, __VMLINUX_SYMBOL_STR(fbtft_write_vmem16_bus16) },
	{ 0x4c234460, __VMLINUX_SYMBOL_STR(fbtft_write_gpio16_wr) },
	{ 0x82000cb5, __VMLINUX_SYMBOL_STR(fbtft_write_gpio16_wr_latched) },
	{ 0xac6e7346, __VMLINUX_SYMBOL_STR(fbtft_write_reg16_bus16) },
	{ 0x694dec21, __VMLINUX_SYMBOL_STR(fbtft_write_vmem16_bus8) },
	{ 0xa5a7c5a3, __VMLINUX_SYMBOL_STR(fbtft_framebuffer_release) },
	{ 0x34c5dc7b, __VMLINUX_SYMBOL_STR(fbtft_register_framebuffer) },
	{ 0x4458706b, __VMLINUX_SYMBOL_STR(fbtft_register_backlight) },
	{ 0xbef1b4c3, __VMLINUX_SYMBOL_STR(fbtft_write_reg8_bus8) },
	{ 0x2484d95b, __VMLINUX_SYMBOL_STR(fbtft_write_vmem16_bus9) },
	{ 0x37f98183, __VMLINUX_SYMBOL_STR(fbtft_write_reg8_bus9) },
	{ 0xe70bf3f8, __VMLINUX_SYMBOL_STR(fbtft_write_spi) },
	{ 0xdc221be7, __VMLINUX_SYMBOL_STR(fbtft_write_reg16_bus8) },
	{ 0x63f15b45, __VMLINUX_SYMBOL_STR(fbtft_init_display) },
	{ 0x3ab378ee, __VMLINUX_SYMBOL_STR(fbtft_framebuffer_alloc) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=fbtft";

MODULE_ALIAS("platform:flexpfb");

MODULE_INFO(srcversion, "9E07BAAD97C0FDB23DEA9C2");
