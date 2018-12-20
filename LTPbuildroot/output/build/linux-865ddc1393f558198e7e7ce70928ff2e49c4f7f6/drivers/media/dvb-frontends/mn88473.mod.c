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
	{ 0xc22e7785, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x79c26f50, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6046a31a, __VMLINUX_SYMBOL_STR(i2c_new_dummy) },
	{ 0x363410f7, __VMLINUX_SYMBOL_STR(__regmap_init_i2c) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2ebcd9e7, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x9f6efab6, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x9792ee10, __VMLINUX_SYMBOL_STR(regmap_bulk_write) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xe5ae8707, __VMLINUX_SYMBOL_STR(intlog10) },
	{ 0x16f5d457, __VMLINUX_SYMBOL_STR(regmap_bulk_read) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2a7cfbcb, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0x3844c3fe, __VMLINUX_SYMBOL_STR(regmap_exit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dvb-core";

MODULE_ALIAS("i2c:mn88473");

MODULE_INFO(srcversion, "D1D6BC27D1A4F3DCFDBDB0D");
