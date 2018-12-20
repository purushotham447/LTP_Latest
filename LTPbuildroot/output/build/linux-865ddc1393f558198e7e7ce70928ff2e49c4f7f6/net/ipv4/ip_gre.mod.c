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
	{ 0x3828f72e, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xdc06580a, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x66bf1e0b, __VMLINUX_SYMBOL_STR(ip_tunnel_get_iflink) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x8eb8c602, __VMLINUX_SYMBOL_STR(metadata_dst_alloc) },
	{ 0x6567fe23, __VMLINUX_SYMBOL_STR(icmp_send) },
	{ 0xc2cad502, __VMLINUX_SYMBOL_STR(ipv4_update_pmtu) },
	{ 0x9134c1e9, __VMLINUX_SYMBOL_STR(ip_tunnel_lookup) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x33931b7d, __VMLINUX_SYMBOL_STR(__ip_tunnel_change_mtu) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x7d4d34d6, __VMLINUX_SYMBOL_STR(dst_cache_get_ip4) },
	{ 0x50e22dec, __VMLINUX_SYMBOL_STR(ip_tunnel_xmit) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xf4bd463c, __VMLINUX_SYMBOL_STR(__iptunnel_pull_header) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5375aed5, __VMLINUX_SYMBOL_STR(ip_tunnel_setup) },
	{ 0x7c63a2d6, __VMLINUX_SYMBOL_STR(ip_tunnel_dellink) },
	{ 0xfd934f04, __VMLINUX_SYMBOL_STR(skb_checksum) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xbbaa7d81, __VMLINUX_SYMBOL_STR(gre_add_protocol) },
	{ 0xf7995a5c, __VMLINUX_SYMBOL_STR(ip_tunnel_newlink) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x53b0e41, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0x39b2ee35, __VMLINUX_SYMBOL_STR(ip_tunnel_uninit) },
	{ 0xac4c7e42, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xa1738c18, __VMLINUX_SYMBOL_STR(gre_del_protocol) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xf3da8e98, __VMLINUX_SYMBOL_STR(iptunnel_xmit) },
	{ 0x758b73d2, __VMLINUX_SYMBOL_STR(ip_tunnel_delete_net) },
	{ 0xb5370902, __VMLINUX_SYMBOL_STR(ip_tunnel_init) },
	{ 0xbd8b1a6, __VMLINUX_SYMBOL_STR(ip_tunnel_get_link_net) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x75ebe0f4, __VMLINUX_SYMBOL_STR(ip_tunnel_ioctl) },
	{ 0xdf55d05, __VMLINUX_SYMBOL_STR(ip_tunnel_changelink) },
	{ 0xdd41fc2f, __VMLINUX_SYMBOL_STR(rtnl_configure_link) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xd6c3b770, __VMLINUX_SYMBOL_STR(ipv4_redirect) },
	{ 0xf4c95eee, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xb4e5d113, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x83c9d68c, __VMLINUX_SYMBOL_STR(ip_tunnel_init_net) },
	{ 0xf0891e16, __VMLINUX_SYMBOL_STR(iptunnel_handle_offloads) },
	{ 0xa0f1874e, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x8b644bb8, __VMLINUX_SYMBOL_STR(rtnl_create_link) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x4d530717, __VMLINUX_SYMBOL_STR(ip6_err_gen_icmpv6_unreach) },
	{ 0xff3d718f, __VMLINUX_SYMBOL_STR(___pskb_trim) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0xac7beeab, __VMLINUX_SYMBOL_STR(dst_cache_set_ip4) },
	{ 0xe85c733f, __VMLINUX_SYMBOL_STR(ip_tunnel_encap_setup) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0x4632fcab, __VMLINUX_SYMBOL_STR(ip_tunnel_change_mtu) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0xe983adc3, __VMLINUX_SYMBOL_STR(gre_parse_header) },
	{ 0x6ca91150, __VMLINUX_SYMBOL_STR(ip_tunnel_rcv) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel,gre,ipv6";


MODULE_INFO(srcversion, "0E17EAC82415CD7519AEE24");
