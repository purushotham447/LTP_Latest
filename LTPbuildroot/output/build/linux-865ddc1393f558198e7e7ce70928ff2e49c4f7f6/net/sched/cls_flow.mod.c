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
	{ 0xe3d4f9b9, __VMLINUX_SYMBOL_STR(unregister_tcf_proto_ops) },
	{ 0x7b781f63, __VMLINUX_SYMBOL_STR(register_tcf_proto_ops) },
	{ 0x93674df4, __VMLINUX_SYMBOL_STR(__skb_flow_dissect) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x4ee3e2cd, __VMLINUX_SYMBOL_STR(__tcf_em_tree_match) },
	{ 0x77cfe13e, __VMLINUX_SYMBOL_STR(from_kuid) },
	{ 0x5f66a728, __VMLINUX_SYMBOL_STR(from_kgid) },
	{ 0xebf73c2a, __VMLINUX_SYMBOL_STR(__skb_get_hash) },
	{ 0xd437c286, __VMLINUX_SYMBOL_STR(flow_get_u32_src) },
	{ 0x655244b2, __VMLINUX_SYMBOL_STR(tcf_action_exec) },
	{ 0xc5990f22, __VMLINUX_SYMBOL_STR(flow_keys_dissector) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xad94cdc6, __VMLINUX_SYMBOL_STR(flow_get_u32_dst) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x6833b73d, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0xfa67501e, __VMLINUX_SYMBOL_STR(tcf_exts_validate) },
	{ 0x75e75d81, __VMLINUX_SYMBOL_STR(tcf_em_tree_validate) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x39a701c6, __VMLINUX_SYMBOL_STR(__put_net) },
	{ 0xcd2c8e9c, __VMLINUX_SYMBOL_STR(tcf_em_tree_destroy) },
	{ 0x54144963, __VMLINUX_SYMBOL_STR(tcf_exts_destroy) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x8a39f742, __VMLINUX_SYMBOL_STR(tcf_queue_work) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xb7aa5532, __VMLINUX_SYMBOL_STR(tcf_exts_dump_stats) },
	{ 0x431acd4f, __VMLINUX_SYMBOL_STR(tcf_em_tree_dump) },
	{ 0xee7d0f46, __VMLINUX_SYMBOL_STR(tcf_exts_dump) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EF9B5D4A5CA6F3AA4A8286E");
