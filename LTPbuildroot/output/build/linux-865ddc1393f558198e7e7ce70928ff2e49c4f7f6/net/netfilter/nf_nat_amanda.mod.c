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
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0x92785d25, __VMLINUX_SYMBOL_STR(nf_nat_amanda_hook) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x6ba7c8a3, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0x317ad3e2, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x6fd1cdbe, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0x86703d9b, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0x1e1deb22, __VMLINUX_SYMBOL_STR(nf_nat_follow_master) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack_amanda,nf_conntrack,nf_nat";


MODULE_INFO(srcversion, "DACA3B509420FBE2DA0B4A1");
