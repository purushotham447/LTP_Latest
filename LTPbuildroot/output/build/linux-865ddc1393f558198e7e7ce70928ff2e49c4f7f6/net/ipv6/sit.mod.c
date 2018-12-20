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
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xbd8b1a6, __VMLINUX_SYMBOL_STR(ip_tunnel_get_link_net) },
	{ 0x66bf1e0b, __VMLINUX_SYMBOL_STR(ip_tunnel_get_iflink) },
	{ 0xdc06580a, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x75cee6ad, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_register) },
	{ 0x3828f72e, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x53b0e41, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0x40c694fc, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_deregister) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x32b890e3, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xb8b6bd8e, __VMLINUX_SYMBOL_STR(icmpv6_send) },
	{ 0xe3056ee7, __VMLINUX_SYMBOL_STR(neigh_destroy) },
	{ 0xf3da8e98, __VMLINUX_SYMBOL_STR(iptunnel_xmit) },
	{ 0xe4bfb774, __VMLINUX_SYMBOL_STR(iptun_encaps) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x50579830, __VMLINUX_SYMBOL_STR(skb_set_owner_w) },
	{ 0x2f390b4c, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0xf6c9cbcd, __VMLINUX_SYMBOL_STR(ipv6_chk_prefix) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x928efb87, __VMLINUX_SYMBOL_STR(ipv6_chk_custom_prefix) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x3e72ef7b, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x50e22dec, __VMLINUX_SYMBOL_STR(ip_tunnel_xmit) },
	{ 0xf0891e16, __VMLINUX_SYMBOL_STR(iptunnel_handle_offloads) },
	{ 0xedf01cff, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xe85c733f, __VMLINUX_SYMBOL_STR(ip_tunnel_encap_setup) },
	{ 0xac4c7e42, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x62849ac7, __VMLINUX_SYMBOL_STR(dev_valid_name) },
	{ 0x375708c2, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x5f8504e7, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x38a8ceb5, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x6ca91150, __VMLINUX_SYMBOL_STR(ip_tunnel_rcv) },
	{ 0xf4bd463c, __VMLINUX_SYMBOL_STR(__iptunnel_pull_header) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xc2cad502, __VMLINUX_SYMBOL_STR(ipv4_update_pmtu) },
	{ 0xd6c3b770, __VMLINUX_SYMBOL_STR(ipv4_redirect) },
	{ 0x4d530717, __VMLINUX_SYMBOL_STR(ip6_err_gen_icmpv6_unreach) },
	{ 0xe9474bde, __VMLINUX_SYMBOL_STR(dst_cache_init) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x6c209eab, __VMLINUX_SYMBOL_STR(__alloc_percpu_gfp) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0xada38766, __VMLINUX_SYMBOL_STR(dst_cache_destroy) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0xe1043ec8, __VMLINUX_SYMBOL_STR(netdev_state_change) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0xbe4a6c67, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa0f1874e, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xf6f927, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel,tunnel4,ipv6";


MODULE_INFO(srcversion, "6C0A6C6B9F1BF189B6236E5");
