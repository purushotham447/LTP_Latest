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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c62a2f0, __VMLINUX_SYMBOL_STR(crypto_unregister_skciphers) },
	{ 0xefe73979, __VMLINUX_SYMBOL_STR(simd_skcipher_free) },
	{ 0xfec4233a, __VMLINUX_SYMBOL_STR(__crypto_xor) },
	{ 0xa8a8110c, __VMLINUX_SYMBOL_STR(kernel_neon_end) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x88638552, __VMLINUX_SYMBOL_STR(simd_skcipher_create_compat) },
	{ 0xf40b2297, __VMLINUX_SYMBOL_STR(__crypto_memneq) },
	{ 0xb8314512, __VMLINUX_SYMBOL_STR(skcipher_walk_done) },
	{ 0x24aac4d9, __VMLINUX_SYMBOL_STR(crypto_aes_expand_key) },
	{ 0xfd516d7b, __VMLINUX_SYMBOL_STR(crypto_register_skciphers) },
	{ 0x4281e385, __VMLINUX_SYMBOL_STR(skcipher_walk_virt) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x3d3c540f, __VMLINUX_SYMBOL_STR(elf_hwcap) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x8fd180e7, __VMLINUX_SYMBOL_STR(kernel_neon_begin) },
	{ 0xa37e1a, __VMLINUX_SYMBOL_STR(crypto_alloc_base) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=crypto_simd";


MODULE_INFO(srcversion, "BFD306F056967D7D54517F4");
