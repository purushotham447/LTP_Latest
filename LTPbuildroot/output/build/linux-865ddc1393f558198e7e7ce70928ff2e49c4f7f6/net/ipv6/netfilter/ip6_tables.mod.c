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
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x357f917e, __VMLINUX_SYMBOL_STR(xt_unregister_table) },
	{ 0x24c8e482, __VMLINUX_SYMBOL_STR(xt_copy_counters_from_user) },
	{ 0x40728a63, __VMLINUX_SYMBOL_STR(xt_find_revision) },
	{ 0x7aa1756e, __VMLINUX_SYMBOL_STR(kvfree) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe381414a, __VMLINUX_SYMBOL_STR(xt_check_target) },
	{ 0x2bf9fbd4, __VMLINUX_SYMBOL_STR(xt_register_matches) },
	{ 0x9c995c69, __VMLINUX_SYMBOL_STR(xt_percpu_counter_alloc) },
	{ 0xd87ae60d, __VMLINUX_SYMBOL_STR(xt_check_entry_offsets) },
	{ 0xd8baf5fd, __VMLINUX_SYMBOL_STR(xt_proto_fini) },
	{ 0x6462533a, __VMLINUX_SYMBOL_STR(xt_table_unlock) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xcb3e91cc, __VMLINUX_SYMBOL_STR(xt_counters_alloc) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xbd8de731, __VMLINUX_SYMBOL_STR(xt_find_table_lock) },
	{ 0x9399617d, __VMLINUX_SYMBOL_STR(ipv6_find_hdr) },
	{ 0xc208f63f, __VMLINUX_SYMBOL_STR(xt_replace_table) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0xb345b9ff, __VMLINUX_SYMBOL_STR(xt_proto_init) },
	{ 0x19e63511, __VMLINUX_SYMBOL_STR(xt_register_table) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x8cf43c9b, __VMLINUX_SYMBOL_STR(xt_target_to_user) },
	{ 0xd7f5fcd, __VMLINUX_SYMBOL_STR(xt_alloc_entry_offsets) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x44d0848a, __VMLINUX_SYMBOL_STR(nf_unregister_net_hooks) },
	{ 0x32b890e3, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0xe1901a9, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xf72caa6d, __VMLINUX_SYMBOL_STR(nf_log_trace) },
	{ 0x807d2b2c, __VMLINUX_SYMBOL_STR(xt_recseq) },
	{ 0xe75770b6, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0xd142bfaf, __VMLINUX_SYMBOL_STR(nf_register_net_hooks) },
	{ 0x7672f84a, __VMLINUX_SYMBOL_STR(nf_unregister_sockopt) },
	{ 0x3e58cac0, __VMLINUX_SYMBOL_STR(xt_tee_enabled) },
	{ 0xeaca346c, __VMLINUX_SYMBOL_STR(xt_request_find_match) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x62dd1d2, __VMLINUX_SYMBOL_STR(xt_unregister_matches) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xb286687c, __VMLINUX_SYMBOL_STR(xt_request_find_target) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x70c52dc5, __VMLINUX_SYMBOL_STR(nf_skb_duplicated) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xcfe4aed6, __VMLINUX_SYMBOL_STR(xt_check_match) },
	{ 0xfef779fa, __VMLINUX_SYMBOL_STR(xt_find_jump_offset) },
	{ 0xbfacb837, __VMLINUX_SYMBOL_STR(xt_percpu_counter_free) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0xc4394d36, __VMLINUX_SYMBOL_STR(nf_register_sockopt) },
	{ 0x555c3243, __VMLINUX_SYMBOL_STR(xt_alloc_table_info) },
	{ 0x16ff5f5e, __VMLINUX_SYMBOL_STR(xt_match_to_user) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xa48b3a97, __VMLINUX_SYMBOL_STR(xt_free_table_info) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";


MODULE_INFO(srcversion, "E7DBED13A3DC0C8FA0F696A");
