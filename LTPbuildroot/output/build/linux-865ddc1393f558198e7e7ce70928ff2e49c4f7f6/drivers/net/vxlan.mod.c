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
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0xcd24396f, __VMLINUX_SYMBOL_STR(neigh_lookup) },
	{ 0x901e1532, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xdc06580a, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x55cb9f3e, __VMLINUX_SYMBOL_STR(ip_mc_leave_group) },
	{ 0xcdaa2e34, __VMLINUX_SYMBOL_STR(udp_tunnel_notify_del_rx_port) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x1133c9e, __VMLINUX_SYMBOL_STR(ip_tunnel_metadata_cnt) },
	{ 0xcd3da1e4, __VMLINUX_SYMBOL_STR(arp_tbl) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x519704ac, __VMLINUX_SYMBOL_STR(udp_tunnel_xmit_skb) },
	{ 0x91922e72, __VMLINUX_SYMBOL_STR(rtnl_notify) },
	{ 0xabc23289, __VMLINUX_SYMBOL_STR(dst_cache_set_ip6) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xdf7e14f0, __VMLINUX_SYMBOL_STR(udp_tun_rx_dst) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x7d4d34d6, __VMLINUX_SYMBOL_STR(dst_cache_get_ip4) },
	{ 0x441a2114, __VMLINUX_SYMBOL_STR(dst_cache_get_ip6) },
	{ 0xe3056ee7, __VMLINUX_SYMBOL_STR(neigh_destroy) },
	{ 0xd56dec15, __VMLINUX_SYMBOL_STR(skb_scrub_packet) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x40273fa7, __VMLINUX_SYMBOL_STR(udp_sock_create6) },
	{ 0x90de636a, __VMLINUX_SYMBOL_STR(setup_udp_tunnel_sock) },
	{ 0x3e72ef7b, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xf4bd463c, __VMLINUX_SYMBOL_STR(__iptunnel_pull_header) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0xf0d5d424, __VMLINUX_SYMBOL_STR(udp_tunnel_sock_release) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb2726c02, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0x6833df51, __VMLINUX_SYMBOL_STR(arp_create) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdc6a2165, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x333bd3c0, __VMLINUX_SYMBOL_STR(udp_tunnel_push_rx_port) },
	{ 0x7d38c86a, __VMLINUX_SYMBOL_STR(ip_mc_join_group) },
	{ 0xac4c7e42, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x38a9f7c5, __VMLINUX_SYMBOL_STR(in6addr_loopback) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x3b7026e, __VMLINUX_SYMBOL_STR(gro_cells_receive) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x7ed623ae, __VMLINUX_SYMBOL_STR(ipv6_stub) },
	{ 0xebf73c2a, __VMLINUX_SYMBOL_STR(__skb_get_hash) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0xbe4a6c67, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x6c209eab, __VMLINUX_SYMBOL_STR(__alloc_percpu_gfp) },
	{ 0x8e983d97, __VMLINUX_SYMBOL_STR(peernet2id) },
	{ 0xdd41fc2f, __VMLINUX_SYMBOL_STR(rtnl_configure_link) },
	{ 0xdadc5274, __VMLINUX_SYMBOL_STR(eth_gro_receive) },
	{ 0xf4c347b9, __VMLINUX_SYMBOL_STR(rtnl_set_sk_err) },
	{ 0xf7a33ca7, __VMLINUX_SYMBOL_STR(eth_gro_complete) },
	{ 0xe9474bde, __VMLINUX_SYMBOL_STR(dst_cache_init) },
	{ 0x20a5503, __VMLINUX_SYMBOL_STR(udp_tunnel_notify_add_rx_port) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xada38766, __VMLINUX_SYMBOL_STR(dst_cache_destroy) },
	{ 0xa56a787, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xf4c95eee, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xcad5f161, __VMLINUX_SYMBOL_STR(udp_tunnel_drop_rx_port) },
	{ 0xb4e5d113, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x9f54ead7, __VMLINUX_SYMBOL_STR(gro_cells_destroy) },
	{ 0xf0891e16, __VMLINUX_SYMBOL_STR(iptunnel_handle_offloads) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xf6f927, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xa0f1874e, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x8b644bb8, __VMLINUX_SYMBOL_STR(rtnl_create_link) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xd9edc7e6, __VMLINUX_SYMBOL_STR(gro_cells_init) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x44da5d0f, __VMLINUX_SYMBOL_STR(__csum_ipv6_magic) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x54b9ebbd, __VMLINUX_SYMBOL_STR(udp_tunnel6_xmit_skb) },
	{ 0xac7beeab, __VMLINUX_SYMBOL_STR(dst_cache_set_ip4) },
	{ 0xf8050eb1, __VMLINUX_SYMBOL_STR(udp_sock_create4) },
	{ 0x7d0db45c, __VMLINUX_SYMBOL_STR(jiffies_to_clock_t) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x8d13991e, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x74f77355, __VMLINUX_SYMBOL_STR(ip6_dst_hoplimit) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x4620712e, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0xde0c5c76, __VMLINUX_SYMBOL_STR(inet_get_local_port_range) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xe43180c4, __VMLINUX_SYMBOL_STR(__skb_checksum_complete) },
	{ 0x200b2041, __VMLINUX_SYMBOL_STR(in6addr_any) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=udp_tunnel,ip6_udp_tunnel";


MODULE_INFO(srcversion, "9C621102F7C994310D6B40A");
