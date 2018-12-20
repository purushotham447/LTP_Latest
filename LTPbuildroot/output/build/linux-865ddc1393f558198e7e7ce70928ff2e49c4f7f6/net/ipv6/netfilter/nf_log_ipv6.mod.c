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
	{ 0x93c2f7b6, __VMLINUX_SYMBOL_STR(nf_log_unregister) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x918721c2, __VMLINUX_SYMBOL_STR(nf_log_register) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x80c68137, __VMLINUX_SYMBOL_STR(nf_log_buf_close) },
	{ 0x15ac325, __VMLINUX_SYMBOL_STR(nf_log_dump_packet_common) },
	{ 0xd4961de, __VMLINUX_SYMBOL_STR(nf_log_buf_open) },
	{ 0x9aaeefce, __VMLINUX_SYMBOL_STR(sysctl_nf_log_all_netns) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x84fc35a8, __VMLINUX_SYMBOL_STR(nf_log_set) },
	{ 0xc9fb3932, __VMLINUX_SYMBOL_STR(nf_log_unset) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xec1b9f42, __VMLINUX_SYMBOL_STR(nf_log_dump_sk_uid_gid) },
	{ 0x23033f66, __VMLINUX_SYMBOL_STR(nf_log_dump_udp_header) },
	{ 0xc2ed08ef, __VMLINUX_SYMBOL_STR(nf_log_dump_tcp_header) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x487c5d33, __VMLINUX_SYMBOL_STR(nf_log_buf_add) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_log_common";


MODULE_INFO(srcversion, "93A7A703394DD78322F458B");
