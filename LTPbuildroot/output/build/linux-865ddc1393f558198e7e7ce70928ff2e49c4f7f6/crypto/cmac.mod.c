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
	{ 0x9d7e240c, __VMLINUX_SYMBOL_STR(crypto_unregister_template) },
	{ 0xc0304434, __VMLINUX_SYMBOL_STR(crypto_register_template) },
	{ 0xcac02a96, __VMLINUX_SYMBOL_STR(shash_register_instance) },
	{ 0xfc7820c, __VMLINUX_SYMBOL_STR(shash_free_instance) },
	{ 0xcfdd60c8, __VMLINUX_SYMBOL_STR(crypto_init_spawn) },
	{ 0x17edb74b, __VMLINUX_SYMBOL_STR(crypto_alloc_instance2) },
	{ 0x74fce698, __VMLINUX_SYMBOL_STR(crypto_mod_put) },
	{ 0x43676a90, __VMLINUX_SYMBOL_STR(crypto_attr_alg2) },
	{ 0xd16712f3, __VMLINUX_SYMBOL_STR(crypto_check_attr_type) },
	{ 0x1d0bc38a, __VMLINUX_SYMBOL_STR(crypto_spawn_tfm) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfec4233a, __VMLINUX_SYMBOL_STR(__crypto_xor) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7C08B70E5C33A7CF63CF7AC");
