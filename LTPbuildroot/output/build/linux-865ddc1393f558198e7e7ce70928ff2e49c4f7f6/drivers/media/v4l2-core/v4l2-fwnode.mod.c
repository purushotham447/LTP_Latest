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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x589d6d9b, __VMLINUX_SYMBOL_STR(fwnode_handle_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x6908172b, __VMLINUX_SYMBOL_STR(fwnode_get_next_parent) },
	{ 0x673753ac, __VMLINUX_SYMBOL_STR(fwnode_property_present) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0x7576f8e7, __VMLINUX_SYMBOL_STR(fwnode_property_read_u64_array) },
	{ 0x633676d2, __VMLINUX_SYMBOL_STR(fwnode_property_read_u32_array) },
	{ 0x33af78c3, __VMLINUX_SYMBOL_STR(fwnode_graph_parse_endpoint) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x7eccdc13, __VMLINUX_SYMBOL_STR(fwnode_get_parent) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5b46922f, __VMLINUX_SYMBOL_STR(fwnode_graph_get_remote_endpoint) },
	{ 0x17dfd516, __VMLINUX_SYMBOL_STR(of_fwnode_ops) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "AA3CF0E3CC10AEE6D9A016D");
