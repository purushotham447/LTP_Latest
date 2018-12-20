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
	{ 0x6f3952e7, __VMLINUX_SYMBOL_STR(crypto_alloc_skcipher) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa239fa57, __VMLINUX_SYMBOL_STR(cryptd_free_skcipher) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xa3e3edbb, __VMLINUX_SYMBOL_STR(cryptd_skcipher_queued) },
	{ 0xbbf2e2f3, __VMLINUX_SYMBOL_STR(crypto_unregister_skcipher) },
	{ 0xa3f389d9, __VMLINUX_SYMBOL_STR(crypto_register_skcipher) },
	{ 0x83991ebf, __VMLINUX_SYMBOL_STR(cryptd_alloc_skcipher) },
	{ 0xf6c105ed, __VMLINUX_SYMBOL_STR(cryptd_skcipher_child) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cryptd";


MODULE_INFO(srcversion, "3F575CB489AAED55E310F90");
