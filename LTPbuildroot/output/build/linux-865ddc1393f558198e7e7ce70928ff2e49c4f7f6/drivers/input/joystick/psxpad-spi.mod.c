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
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x7bd5aecd, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0xff3e3628, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xd8b9dad3, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x14619f2, __VMLINUX_SYMBOL_STR(input_register_polled_device) },
	{ 0xad6d813b, __VMLINUX_SYMBOL_STR(spi_setup) },
	{ 0xf12c4c3d, __VMLINUX_SYMBOL_STR(input_ff_create_memless) },
	{ 0x34903431, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x12212cd, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x2b8642e2, __VMLINUX_SYMBOL_STR(input_allocate_polled_device) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x13cae825, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=input-polldev,ff-memless";

MODULE_ALIAS("spi:psxpad-spi");

MODULE_INFO(srcversion, "91F72A2EFA37875F420F3E2");
