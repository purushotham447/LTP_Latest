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
	{ 0x5f8504e7, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x61e8d1c6, __VMLINUX_SYMBOL_STR(gro_find_receive_by_type) },
	{ 0xc3aaa741, __VMLINUX_SYMBOL_STR(dev_change_flags) },
	{ 0xfd885838, __VMLINUX_SYMBOL_STR(dev_mc_unsync) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc8cd661, __VMLINUX_SYMBOL_STR(dev_get_flags) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xd44eb378, __VMLINUX_SYMBOL_STR(dev_get_nest_level) },
	{ 0xb8fc717e, __VMLINUX_SYMBOL_STR(garp_uninit_applicant) },
	{ 0xdc03ceca, __VMLINUX_SYMBOL_STR(vlan_dev_vlan_id) },
	{ 0x5ebf4ed7, __VMLINUX_SYMBOL_STR(dev_uc_add) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xfc7e0c3a, __VMLINUX_SYMBOL_STR(garp_request_join) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x8a1ba6d9, __VMLINUX_SYMBOL_STR(vlan_uses_dev) },
	{ 0xd6d7cce4, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0xcdd58911, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xbcf4d91d, __VMLINUX_SYMBOL_STR(dev_set_allmulti) },
	{ 0x6ebf444b, __VMLINUX_SYMBOL_STR(vlan_vid_del) },
	{ 0x62d5cdcf, __VMLINUX_SYMBOL_STR(call_netdevice_notifiers) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xb0a7c4, __VMLINUX_SYMBOL_STR(linkwatch_fire_event) },
	{ 0xb1907500, __VMLINUX_SYMBOL_STR(dev_add_offload) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x21ab8006, __VMLINUX_SYMBOL_STR(vlan_vid_add) },
	{ 0x89294f6, __VMLINUX_SYMBOL_STR(__netpoll_setup) },
	{ 0x6a489f83, __VMLINUX_SYMBOL_STR(garp_init_applicant) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0xd54c3c6f, __VMLINUX_SYMBOL_STR(proc_remove) },
	{ 0x92037625, __VMLINUX_SYMBOL_STR(vlan_ioctl_set) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x1dbc7f6c, __VMLINUX_SYMBOL_STR(netpoll_send_skb_on_dev) },
	{ 0xbac2cb51, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xc2209c8f, __VMLINUX_SYMBOL_STR(__ethtool_get_link_ksettings) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdc6a2165, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x32b890e3, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x26bc40ef, __VMLINUX_SYMBOL_STR(__netpoll_free_async) },
	{ 0xac4c7e42, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x7b62972b, __VMLINUX_SYMBOL_STR(garp_register_application) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73b64e0b, __VMLINUX_SYMBOL_STR(netdev_upper_dev_unlink) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xe50dc563, __VMLINUX_SYMBOL_STR(dev_remove_offload) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x18d866d0, __VMLINUX_SYMBOL_STR(proc_mkdir_data) },
	{ 0xe37ae932, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0xf24ae713, __VMLINUX_SYMBOL_STR(netif_stacked_transfer_operstate) },
	{ 0x2027a172, __VMLINUX_SYMBOL_STR(gro_find_complete_by_type) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0xbe4a6c67, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0xbd002d5c, __VMLINUX_SYMBOL_STR(garp_request_leave) },
	{ 0x6c209eab, __VMLINUX_SYMBOL_STR(__alloc_percpu_gfp) },
	{ 0xd2c6624d, __VMLINUX_SYMBOL_STR(nla_validate) },
	{ 0xdf8aeaf6, __VMLINUX_SYMBOL_STR(eth_header_parse) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x375708c2, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xe03eec4f, __VMLINUX_SYMBOL_STR(netdev_upper_dev_link) },
	{ 0xb4e5d113, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x8140c735, __VMLINUX_SYMBOL_STR(dev_uc_unsync) },
	{ 0xfa9fefbe, __VMLINUX_SYMBOL_STR(__dev_get_by_name) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x907d92cc, __VMLINUX_SYMBOL_STR(garp_unregister_application) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xf6f927, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0x542a3c2e, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0x5f487a65, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x1faede42, __VMLINUX_SYMBOL_STR(dev_set_promiscuity) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa86cdd09, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0x58b4645c, __VMLINUX_SYMBOL_STR(dev_close_many) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x50e183ad, __VMLINUX_SYMBOL_STR(dev_uc_del) },
	{ 0x9e14c149, __VMLINUX_SYMBOL_STR(dev_uc_sync) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0xcff2892b, __VMLINUX_SYMBOL_STR(netdev_update_features) },
	{ 0x2a628db, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x81f8afb7, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0xeff24055, __VMLINUX_SYMBOL_STR(dev_mc_sync) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x26ef7523, __VMLINUX_SYMBOL_STR(dev_get_stats) },
	{ 0x62cfea0b, __VMLINUX_SYMBOL_STR(dev_set_mtu) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=garp";


MODULE_INFO(srcversion, "ECF7DE26F31F7B120D6DB50");
