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
	{ 0xca90ff30, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xfd72abf8, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x6ff41f85, __VMLINUX_SYMBOL_STR(usbnet_get_stats64) },
	{ 0x31a2b829, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0xffc0b433, __VMLINUX_SYMBOL_STR(cdc_ncm_change_mtu) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x47e76171, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x2f2cec8d, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x5c61cfec, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xab45e185, __VMLINUX_SYMBOL_STR(usb_match_id) },
	{ 0x8cd0b45a, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xfc1e323d, __VMLINUX_SYMBOL_STR(usb_cdc_wdm_register) },
	{ 0xfaf3fcb2, __VMLINUX_SYMBOL_STR(cdc_ncm_bind_common) },
	{ 0x9c0d48ad, __VMLINUX_SYMBOL_STR(cdc_ncm_select_altsetting) },
	{ 0x75d0802d, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x66996915, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x3faf3652, __VMLINUX_SYMBOL_STR(cdc_ncm_unbind) },
	{ 0x44e0f020, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0xcdb2fd03, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0xd6f91c86, __VMLINUX_SYMBOL_STR(in6_dev_finish_destroy) },
	{ 0x778293d, __VMLINUX_SYMBOL_STR(__vlan_find_dev_deep_rcu) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0xc1ed1633, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x418e630e, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xa1915413, __VMLINUX_SYMBOL_STR(cdc_ncm_rx_verify_ndp16) },
	{ 0x7ed623ae, __VMLINUX_SYMBOL_STR(ipv6_stub) },
	{ 0x251ce933, __VMLINUX_SYMBOL_STR(cdc_ncm_rx_verify_nth16) },
	{ 0xf89661b1, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xf5d45fd0, __VMLINUX_SYMBOL_STR(cdc_ncm_fill_tx_frame) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x99ab9445, __VMLINUX_SYMBOL_STR(__dev_kfree_skb_any) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cdc_ncm,cdc-wdm";

MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v0BDBp*d*dc*dsc*dp*ic02isc0Eip00in*");
MODULE_ALIAS("usb:v12D1p*d*dc*dsc*dp*ic02isc0Eip00in*");
MODULE_ALIAS("usb:v03F0pA31Dd*dc*dsc*dp*ic02isc0Eip00in*");
MODULE_ALIAS("usb:v1BC7p1041d*dc*dsc*dp*ic02isc0Eip00in*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc0Eip00in*");

MODULE_INFO(srcversion, "38E9FABC0B5F38EBB589D7C");
