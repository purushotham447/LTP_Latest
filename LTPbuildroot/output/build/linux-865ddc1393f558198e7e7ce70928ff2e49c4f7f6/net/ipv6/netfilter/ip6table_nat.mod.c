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
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xf696567b, __VMLINUX_SYMBOL_STR(ip6t_register_table) },
	{ 0x636dd4b2, __VMLINUX_SYMBOL_STR(ip6t_alloc_initial_table) },
	{ 0x5cee5e1, __VMLINUX_SYMBOL_STR(nf_nat_ipv6_in) },
	{ 0x5efcd644, __VMLINUX_SYMBOL_STR(nf_nat_ipv6_out) },
	{ 0xfbf3646, __VMLINUX_SYMBOL_STR(nf_nat_ipv6_local_fn) },
	{ 0x22b2c395, __VMLINUX_SYMBOL_STR(ip6t_do_table) },
	{ 0xe8a43060, __VMLINUX_SYMBOL_STR(nf_nat_ipv6_fn) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x975044f, __VMLINUX_SYMBOL_STR(ip6t_unregister_table) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip6_tables,nf_nat_ipv6";


MODULE_INFO(srcversion, "617ED6F99ACE5E59B7CEFAE");
