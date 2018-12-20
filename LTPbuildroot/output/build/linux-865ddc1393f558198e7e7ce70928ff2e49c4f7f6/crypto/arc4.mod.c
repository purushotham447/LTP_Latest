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
	{ 0x4f27aa8, __VMLINUX_SYMBOL_STR(crypto_blkcipher_type) },
	{ 0x583451d3, __VMLINUX_SYMBOL_STR(crypto_unregister_algs) },
	{ 0xd9e3bf73, __VMLINUX_SYMBOL_STR(crypto_register_algs) },
	{ 0x1ef3a553, __VMLINUX_SYMBOL_STR(blkcipher_walk_done) },
	{ 0x4605c88c, __VMLINUX_SYMBOL_STR(blkcipher_walk_virt) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A9A70B81DED497247A1C704");
