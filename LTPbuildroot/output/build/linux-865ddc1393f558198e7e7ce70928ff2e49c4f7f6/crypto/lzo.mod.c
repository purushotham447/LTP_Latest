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
	{ 0x94f4e90a, __VMLINUX_SYMBOL_STR(crypto_unregister_scomp) },
	{ 0x587837aa, __VMLINUX_SYMBOL_STR(crypto_unregister_alg) },
	{ 0x35a0b9d, __VMLINUX_SYMBOL_STR(crypto_register_scomp) },
	{ 0x1d3d33f, __VMLINUX_SYMBOL_STR(crypto_register_alg) },
	{ 0x88288e85, __VMLINUX_SYMBOL_STR(kvmalloc_node) },
	{ 0x7aa1756e, __VMLINUX_SYMBOL_STR(kvfree) },
	{ 0x56b63670, __VMLINUX_SYMBOL_STR(lzo1x_1_compress) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf30fda27, __VMLINUX_SYMBOL_STR(lzo1x_decompress_safe) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lzo_compress";


MODULE_INFO(srcversion, "FA5A63789C4817BBE01135E");
