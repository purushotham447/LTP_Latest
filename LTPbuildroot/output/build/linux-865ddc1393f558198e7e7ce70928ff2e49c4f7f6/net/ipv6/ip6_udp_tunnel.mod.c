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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf61b035d, __VMLINUX_SYMBOL_STR(udp6_set_csum) },
	{ 0xdffd2dd8, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xa6c2680, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0xa32c89b4, __VMLINUX_SYMBOL_STR(kernel_setsockopt) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xaffea2cd, __VMLINUX_SYMBOL_STR(kernel_connect) },
	{ 0x55555e79, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0x5517b818, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x4968d2c, __VMLINUX_SYMBOL_STR(ip6_local_out) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "349542EE2427C6C3BDC59F2");
