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
	{ 0xb5cbddc6, __VMLINUX_SYMBOL_STR(xfrm6_rcv) },
	{ 0x99120eee, __VMLINUX_SYMBOL_STR(xfrm6_find_1stfragopt) },
	{ 0x90130c99, __VMLINUX_SYMBOL_STR(ipcomp_output) },
	{ 0x3e8f300d, __VMLINUX_SYMBOL_STR(ipcomp_input) },
	{ 0xb9b04fe6, __VMLINUX_SYMBOL_STR(ipcomp_destroy) },
	{ 0x5134edcb, __VMLINUX_SYMBOL_STR(xfrm6_protocol_deregister) },
	{ 0x41852aac, __VMLINUX_SYMBOL_STR(xfrm_unregister_type) },
	{ 0x62023715, __VMLINUX_SYMBOL_STR(xfrm6_protocol_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe63b4a26, __VMLINUX_SYMBOL_STR(xfrm_register_type) },
	{ 0x517921f6, __VMLINUX_SYMBOL_STR(xfrm_state_insert) },
	{ 0xc7f0a0c0, __VMLINUX_SYMBOL_STR(xfrm_init_state) },
	{ 0xf72be5d6, __VMLINUX_SYMBOL_STR(xfrm6_tunnel_alloc_spi) },
	{ 0x87b5d9d9, __VMLINUX_SYMBOL_STR(xfrm_state_alloc) },
	{ 0x77bad3e, __VMLINUX_SYMBOL_STR(xfrm6_tunnel_spi_lookup) },
	{ 0x11ac1263, __VMLINUX_SYMBOL_STR(ipcomp_init_state) },
	{ 0xb7fc173a, __VMLINUX_SYMBOL_STR(ip6_redirect) },
	{ 0xa23400b1, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0x574a92d1, __VMLINUX_SYMBOL_STR(ip6_update_pmtu) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0x9f82eb6e, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ipv6,xfrm_ipcomp,xfrm6_tunnel";


MODULE_INFO(srcversion, "C15B2E736BD66F150276AF9");
