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
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xe9b690a7, __VMLINUX_SYMBOL_STR(__skb_gso_segment) },
	{ 0x66cdee02, __VMLINUX_SYMBOL_STR(netif_skb_features) },
	{ 0xb8160ad3, __VMLINUX_SYMBOL_STR(skb_gso_transport_seglen) },
	{ 0xb150e26d, __VMLINUX_SYMBOL_STR(__qdisc_calculate_pkt_len) },
	{ 0x57539778, __VMLINUX_SYMBOL_STR(qdisc_watchdog_schedule_ns) },
	{ 0x17f27bb8, __VMLINUX_SYMBOL_STR(qdisc_watchdog_init) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x51f46536, __VMLINUX_SYMBOL_STR(qdisc_reset) },
	{ 0x60526ccc, __VMLINUX_SYMBOL_STR(qdisc_watchdog_cancel) },
	{ 0xa930ef81, __VMLINUX_SYMBOL_STR(fifo_create_dflt) },
	{ 0x5773570d, __VMLINUX_SYMBOL_STR(bfifo_qdisc_ops) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x521b36b5, __VMLINUX_SYMBOL_STR(qdisc_put_rtab) },
	{ 0xed597524, __VMLINUX_SYMBOL_STR(qdisc_get_rtab) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xc64aff23, __VMLINUX_SYMBOL_STR(qdisc_hash_add) },
	{ 0xf2bcd21e, __VMLINUX_SYMBOL_STR(qdisc_destroy) },
	{ 0x5c6397c1, __VMLINUX_SYMBOL_STR(qdisc_tree_reduce_backlog) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xfbcf947e, __VMLINUX_SYMBOL_STR(fifo_set_limit) },
	{ 0x2647072f, __VMLINUX_SYMBOL_STR(noop_qdisc) },
	{ 0xb77131b1, __VMLINUX_SYMBOL_STR(psched_ratecfg_precompute) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xb29ac578, __VMLINUX_SYMBOL_STR(nla_put_64bit) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "080143C29876206D2D28B37");
