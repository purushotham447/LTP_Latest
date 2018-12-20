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
	{ 0x16bc6dfb, __VMLINUX_SYMBOL_STR(unregister_qdisc) },
	{ 0x1b66ccc7, __VMLINUX_SYMBOL_STR(register_qdisc) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x48eedf2a, __VMLINUX_SYMBOL_STR(qdisc_create_dflt) },
	{ 0x36f44cf0, __VMLINUX_SYMBOL_STR(pfifo_qdisc_ops) },
	{ 0x986c9f69, __VMLINUX_SYMBOL_STR(tcf_block_get) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xed874ab8, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x8a95449a, __VMLINUX_SYMBOL_STR(gnet_stats_copy_queue) },
	{ 0x3b032a49, __VMLINUX_SYMBOL_STR(gnet_stats_copy_basic) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xb150e26d, __VMLINUX_SYMBOL_STR(__qdisc_calculate_pkt_len) },
	{ 0xecbbec8, __VMLINUX_SYMBOL_STR(tcf_classify) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x2f390b4c, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x2647072f, __VMLINUX_SYMBOL_STR(noop_qdisc) },
	{ 0x51f46536, __VMLINUX_SYMBOL_STR(qdisc_reset) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x1975a7e6, __VMLINUX_SYMBOL_STR(tcf_block_put) },
	{ 0xf2bcd21e, __VMLINUX_SYMBOL_STR(qdisc_destroy) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "41536C030972CB50113FBEE");
