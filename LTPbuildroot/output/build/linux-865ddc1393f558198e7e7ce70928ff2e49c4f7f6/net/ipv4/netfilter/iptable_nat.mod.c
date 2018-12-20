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
	{ 0xb0b3684c, __VMLINUX_SYMBOL_STR(ipt_register_table) },
	{ 0x45f2ba84, __VMLINUX_SYMBOL_STR(ipt_alloc_initial_table) },
	{ 0xf3f7a6f1, __VMLINUX_SYMBOL_STR(nf_nat_ipv4_in) },
	{ 0x43bdff63, __VMLINUX_SYMBOL_STR(nf_nat_ipv4_out) },
	{ 0x2f50ae0d, __VMLINUX_SYMBOL_STR(nf_nat_ipv4_local_fn) },
	{ 0xcbef2ab5, __VMLINUX_SYMBOL_STR(ipt_do_table) },
	{ 0x1e9d7370, __VMLINUX_SYMBOL_STR(nf_nat_ipv4_fn) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x6c20414c, __VMLINUX_SYMBOL_STR(ipt_unregister_table) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tables,nf_nat_ipv4";


MODULE_INFO(srcversion, "5540E1907C770CB63D5E1EC");
