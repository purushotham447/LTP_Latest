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
	{ 0xb17132a1, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_unregister) },
	{ 0xf4c54fb2, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_register) },
	{ 0x7d44ca65, __VMLINUX_SYMBOL_STR(nat_q931_hook) },
	{ 0x42754118, __VMLINUX_SYMBOL_STR(nat_callforwarding_hook) },
	{ 0x2dbc84a6, __VMLINUX_SYMBOL_STR(nat_h245_hook) },
	{ 0x559716aa, __VMLINUX_SYMBOL_STR(nat_t120_hook) },
	{ 0xfd086aac, __VMLINUX_SYMBOL_STR(nat_rtp_rtcp_hook) },
	{ 0xbd2e6da2, __VMLINUX_SYMBOL_STR(set_ras_addr_hook) },
	{ 0x14a434ae, __VMLINUX_SYMBOL_STR(set_sig_addr_hook) },
	{ 0xc2c181aa, __VMLINUX_SYMBOL_STR(set_h225_addr_hook) },
	{ 0xad2411b7, __VMLINUX_SYMBOL_STR(set_h245_addr_hook) },
	{ 0x6ba7c8a3, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0x3510c0a6, __VMLINUX_SYMBOL_STR(get_h225_addr) },
	{ 0x86703d9b, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x5f2178a, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0x317ad3e2, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0x1e1deb22, __VMLINUX_SYMBOL_STR(nf_nat_follow_master) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x20ea70a, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_conntrack_h323,nf_nat";


MODULE_INFO(srcversion, "A3470AC7ED658EDEEC18B0B");
