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
	{ 0xf4c54fb2, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_register) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xb17132a1, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_unregister) },
	{ 0x3c5746a0, __VMLINUX_SYMBOL_STR(nf_nat_sip_hooks) },
	{ 0xfddb030f, __VMLINUX_SYMBOL_STR(skb_make_writable) },
	{ 0x8355595a, __VMLINUX_SYMBOL_STR(ct_sip_parse_numerical_param) },
	{ 0x91d53c6d, __VMLINUX_SYMBOL_STR(ct_sip_parse_address_param) },
	{ 0x33c09a0e, __VMLINUX_SYMBOL_STR(ct_sip_parse_request) },
	{ 0x2aa0e4fc, __VMLINUX_SYMBOL_STR(strncasecmp) },
	{ 0x13b2cacf, __VMLINUX_SYMBOL_STR(ct_sip_parse_header_uri) },
	{ 0xf2f6f57, __VMLINUX_SYMBOL_STR(nf_ct_seqadj_set) },
	{ 0x6fd1cdbe, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0x6ba7c8a3, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0x86703d9b, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xdf8040ca, __VMLINUX_SYMBOL_STR(ct_sip_get_header) },
	{ 0xd1cada41, __VMLINUX_SYMBOL_STR(ct_sip_get_sdp_header) },
	{ 0x5f2178a, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0x317ad3e2, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x20ea70a, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_conntrack_sip,nf_nat";


MODULE_INFO(srcversion, "9D725F54978D2048992827F");
