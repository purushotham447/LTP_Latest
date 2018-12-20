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
	{ 0x7c63a2d6, __VMLINUX_SYMBOL_STR(ip_tunnel_dellink) },
	{ 0x66bf1e0b, __VMLINUX_SYMBOL_STR(ip_tunnel_get_iflink) },
	{ 0xdc06580a, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x4632fcab, __VMLINUX_SYMBOL_STR(ip_tunnel_change_mtu) },
	{ 0x39b2ee35, __VMLINUX_SYMBOL_STR(ip_tunnel_uninit) },
	{ 0xc6a5104f, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x53b0e41, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0x40c694fc, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_deregister) },
	{ 0xbed9d3be, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x75cee6ad, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_register) },
	{ 0x3828f72e, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x83c9d68c, __VMLINUX_SYMBOL_STR(ip_tunnel_init_net) },
	{ 0x758b73d2, __VMLINUX_SYMBOL_STR(ip_tunnel_delete_net) },
	{ 0x38a8ceb5, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x6ca91150, __VMLINUX_SYMBOL_STR(ip_tunnel_rcv) },
	{ 0x8eb8c602, __VMLINUX_SYMBOL_STR(metadata_dst_alloc) },
	{ 0xf4bd463c, __VMLINUX_SYMBOL_STR(__iptunnel_pull_header) },
	{ 0xd6c3b770, __VMLINUX_SYMBOL_STR(ipv4_redirect) },
	{ 0xc2cad502, __VMLINUX_SYMBOL_STR(ipv4_update_pmtu) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x9134c1e9, __VMLINUX_SYMBOL_STR(ip_tunnel_lookup) },
	{ 0xb5370902, __VMLINUX_SYMBOL_STR(ip_tunnel_init) },
	{ 0x50e22dec, __VMLINUX_SYMBOL_STR(ip_tunnel_xmit) },
	{ 0x3b1ece7, __VMLINUX_SYMBOL_STR(ip_md_tunnel_xmit) },
	{ 0xf0891e16, __VMLINUX_SYMBOL_STR(iptunnel_handle_offloads) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x75ebe0f4, __VMLINUX_SYMBOL_STR(ip_tunnel_ioctl) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x5375aed5, __VMLINUX_SYMBOL_STR(ip_tunnel_setup) },
	{ 0xf7995a5c, __VMLINUX_SYMBOL_STR(ip_tunnel_newlink) },
	{ 0xdf55d05, __VMLINUX_SYMBOL_STR(ip_tunnel_changelink) },
	{ 0xe85c733f, __VMLINUX_SYMBOL_STR(ip_tunnel_encap_setup) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel,tunnel4";


MODULE_INFO(srcversion, "AD2E151F0ADE07D61868B60");
