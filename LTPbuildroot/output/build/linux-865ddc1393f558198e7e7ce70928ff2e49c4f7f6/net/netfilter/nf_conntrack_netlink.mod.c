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
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x1cb9977f, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_unregister) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x61c0840b, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_register) },
	{ 0x9ab82b9f, __VMLINUX_SYMBOL_STR(nf_ct_remove_expectations) },
	{ 0x7473a1c1, __VMLINUX_SYMBOL_STR(nf_conntrack_eventmask_report) },
	{ 0xf5494b75, __VMLINUX_SYMBOL_STR(__nf_ct_try_assign_helper) },
	{ 0x31552eba, __VMLINUX_SYMBOL_STR(nf_conntrack_free) },
	{ 0x518dfb29, __VMLINUX_SYMBOL_STR(nf_conntrack_hash_check_insert) },
	{ 0xac9657d8, __VMLINUX_SYMBOL_STR(ktime_get_with_offset) },
	{ 0x1611dd7d, __VMLINUX_SYMBOL_STR(nf_ct_ext_add) },
	{ 0x3945047c, __VMLINUX_SYMBOL_STR(nf_ct_helper_ext_add) },
	{ 0xbd4f9e04, __VMLINUX_SYMBOL_STR(nf_conntrack_alloc) },
	{ 0xec8beba6, __VMLINUX_SYMBOL_STR(nf_ct_expect_hash) },
	{ 0xc18ac88d, __VMLINUX_SYMBOL_STR(nf_ct_expect_hsize) },
	{ 0x5ce3b588, __VMLINUX_SYMBOL_STR(nfnl_lock) },
	{ 0xdb065657, __VMLINUX_SYMBOL_STR(nfnl_unlock) },
	{ 0x6bf500a5, __VMLINUX_SYMBOL_STR(nfnetlink_parse_nat_setup_hook) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x4b4b24db, __VMLINUX_SYMBOL_STR(nf_conntrack_lock) },
	{ 0x28eff409, __VMLINUX_SYMBOL_STR(nf_conntrack_hash) },
	{ 0x7cfd8c0, __VMLINUX_SYMBOL_STR(nf_conntrack_locks) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0x8ffe7e89, __VMLINUX_SYMBOL_STR(nf_conntrack_htable_size) },
	{ 0x4124ced2, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x2cfa9b17, __VMLINUX_SYMBOL_STR(nfnetlink_send) },
	{ 0x10bef659, __VMLINUX_SYMBOL_STR(nfnetlink_set_err) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xb84152d9, __VMLINUX_SYMBOL_STR(nfnetlink_has_listeners) },
	{ 0x815809d3, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_find_by_symbol) },
	{ 0x1803426f, __VMLINUX_SYMBOL_STR(nf_connlabels_replace) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb31696a6, __VMLINUX_SYMBOL_STR(nf_ct_iterate_cleanup_net) },
	{ 0x999070d1, __VMLINUX_SYMBOL_STR(nf_ct_delete) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x62451f4, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x7050fd8d, __VMLINUX_SYMBOL_STR(__nf_ct_expect_find) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x86703d9b, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0x91fd593c, __VMLINUX_SYMBOL_STR(__nf_conntrack_helper_find) },
	{ 0x7f065e82, __VMLINUX_SYMBOL_STR(nf_conntrack_find_get) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x7d83f6f9, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_find_by_name) },
	{ 0xbbd18f77, __VMLINUX_SYMBOL_STR(nf_ct_expect_alloc) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0xac699aa0, __VMLINUX_SYMBOL_STR(nf_ct_expect_iterate_net) },
	{ 0x21f8f240, __VMLINUX_SYMBOL_STR(nf_ct_unlink_expect_report) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xc2abd2fd, __VMLINUX_SYMBOL_STR(nf_conntrack_expect_lock) },
	{ 0x1dccfc85, __VMLINUX_SYMBOL_STR(nf_ct_expect_find_get) },
	{ 0xd2c6624d, __VMLINUX_SYMBOL_STR(nla_validate) },
	{ 0x7e9fe252, __VMLINUX_SYMBOL_STR(nf_conntrack_l3proto_generic) },
	{ 0x1414ab6d, __VMLINUX_SYMBOL_STR(nf_ct_l3protos) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x6892b89d, __VMLINUX_SYMBOL_STR(nf_ct_expect_put) },
	{ 0x7a02a0bd, __VMLINUX_SYMBOL_STR(__netlink_dump_start) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x32b95b16, __VMLINUX_SYMBOL_STR(nf_ct_expect_register_notifier) },
	{ 0xabfe56b8, __VMLINUX_SYMBOL_STR(nf_conntrack_register_notifier) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x4620712e, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xb29ac578, __VMLINUX_SYMBOL_STR(nla_put_64bit) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x93c544ce, __VMLINUX_SYMBOL_STR(__nf_ct_l4proto_find) },
	{ 0xc9a89751, __VMLINUX_SYMBOL_STR(nf_conntrack_unregister_notifier) },
	{ 0x8ac3f185, __VMLINUX_SYMBOL_STR(nf_ct_expect_unregister_notifier) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nfnetlink,nf_conntrack";


MODULE_INFO(srcversion, "4C04AAD3F13D5209147D60A");
