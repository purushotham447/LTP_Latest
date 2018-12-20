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
	{ 0x66996915, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x75d0802d, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0xca90ff30, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xfd72abf8, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x6ff41f85, __VMLINUX_SYMBOL_STR(usbnet_get_stats64) },
	{ 0x31a2b829, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0x1834ff91, __VMLINUX_SYMBOL_STR(usbnet_change_mtu) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x47e76171, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x2f2cec8d, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x5c61cfec, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x80698041, __VMLINUX_SYMBOL_STR(usbnet_get_endpoints) },
	{ 0xb84ddd76, __VMLINUX_SYMBOL_STR(usbnet_get_ethernet_addr) },
	{ 0xf89661b1, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x901e1532, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x2ac2b7d8, __VMLINUX_SYMBOL_STR(usbnet_write_cmd_async) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x99ab9445, __VMLINUX_SYMBOL_STR(__dev_kfree_skb_any) },
	{ 0xc75481ea, __VMLINUX_SYMBOL_STR(skb_copy_expand) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v09E1p5121d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "8770B7C2A21740EB80A8FE4");
