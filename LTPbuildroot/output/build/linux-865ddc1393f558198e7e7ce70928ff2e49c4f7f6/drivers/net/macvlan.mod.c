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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x33aa810b, __VMLINUX_SYMBOL_STR(dev_forward_skb) },
	{ 0xfd885838, __VMLINUX_SYMBOL_STR(dev_mc_unsync) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd44eb378, __VMLINUX_SYMBOL_STR(dev_get_nest_level) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x5ebf4ed7, __VMLINUX_SYMBOL_STR(dev_uc_add) },
	{ 0x4148a455, __VMLINUX_SYMBOL_STR(__dev_forward_skb) },
	{ 0x7a6c6f04, __VMLINUX_SYMBOL_STR(dev_mc_add_excl) },
	{ 0xa63891fb, __VMLINUX_SYMBOL_STR(netdev_rx_handler_register) },
	{ 0x24d92845, __VMLINUX_SYMBOL_STR(dev_uc_add_excl) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xbcf4d91d, __VMLINUX_SYMBOL_STR(dev_set_allmulti) },
	{ 0x6ebf444b, __VMLINUX_SYMBOL_STR(vlan_vid_del) },
	{ 0x62d5cdcf, __VMLINUX_SYMBOL_STR(call_netdevice_notifiers) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xb0a7c4, __VMLINUX_SYMBOL_STR(linkwatch_fire_event) },
	{ 0x21ab8006, __VMLINUX_SYMBOL_STR(vlan_vid_add) },
	{ 0x89294f6, __VMLINUX_SYMBOL_STR(__netpoll_setup) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x3e72ef7b, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x1dbc7f6c, __VMLINUX_SYMBOL_STR(netpoll_send_skb_on_dev) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb2726c02, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0xea15edd9, __VMLINUX_SYMBOL_STR(dev_set_mac_address) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0xa09a780, __VMLINUX_SYMBOL_STR(ip_check_defrag) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xc2209c8f, __VMLINUX_SYMBOL_STR(__ethtool_get_link_ksettings) },
	{ 0xdc6a2165, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x26bc40ef, __VMLINUX_SYMBOL_STR(__netpoll_free_async) },
	{ 0x44913963, __VMLINUX_SYMBOL_STR(dev_mc_del) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73b64e0b, __VMLINUX_SYMBOL_STR(netdev_upper_dev_unlink) },
	{ 0x5a5f7ce, __VMLINUX_SYMBOL_STR(ndo_dflt_fdb_dump) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xf24ae713, __VMLINUX_SYMBOL_STR(netif_stacked_transfer_operstate) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0xbe4a6c67, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x6c209eab, __VMLINUX_SYMBOL_STR(__alloc_percpu_gfp) },
	{ 0x8b4dbfd0, __VMLINUX_SYMBOL_STR(eth_header_cache_update) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x28e46780, __VMLINUX_SYMBOL_STR(netdev_rx_handler_unregister) },
	{ 0xdf8aeaf6, __VMLINUX_SYMBOL_STR(eth_header_parse) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xc82ddb59, __VMLINUX_SYMBOL_STR(passthru_features_check) },
	{ 0xe03eec4f, __VMLINUX_SYMBOL_STR(netdev_upper_dev_link) },
	{ 0xb4e5d113, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x8140c735, __VMLINUX_SYMBOL_STR(dev_uc_unsync) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xf6f927, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x1faede42, __VMLINUX_SYMBOL_STR(dev_set_promiscuity) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe3642ec5, __VMLINUX_SYMBOL_STR(eth_header_cache) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x50e183ad, __VMLINUX_SYMBOL_STR(dev_uc_del) },
	{ 0x9e14c149, __VMLINUX_SYMBOL_STR(dev_uc_sync) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xcff2892b, __VMLINUX_SYMBOL_STR(netdev_update_features) },
	{ 0x83b7b515, __VMLINUX_SYMBOL_STR(dev_queue_xmit_accel) },
	{ 0x81f8afb7, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0xe136504f, __VMLINUX_SYMBOL_STR(netdev_is_rx_handler_busy) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0xeff24055, __VMLINUX_SYMBOL_STR(dev_mc_sync) },
	{ 0xc58a8cd, __VMLINUX_SYMBOL_STR(netdev_increment_features) },
	{ 0x62cfea0b, __VMLINUX_SYMBOL_STR(dev_set_mtu) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B1D80AAF9CD669A819C508A");
