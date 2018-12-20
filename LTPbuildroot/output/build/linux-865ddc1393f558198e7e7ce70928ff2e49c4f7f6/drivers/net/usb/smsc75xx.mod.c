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
	{ 0xca90ff30, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xfd72abf8, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x6a744329, __VMLINUX_SYMBOL_STR(usbnet_set_link_ksettings) },
	{ 0x79e5e223, __VMLINUX_SYMBOL_STR(usbnet_get_link_ksettings) },
	{ 0x7f343679, __VMLINUX_SYMBOL_STR(usbnet_get_link) },
	{ 0x49936d1f, __VMLINUX_SYMBOL_STR(usbnet_nway_reset) },
	{ 0xe3fcc533, __VMLINUX_SYMBOL_STR(usbnet_set_msglevel) },
	{ 0x2d260f9b, __VMLINUX_SYMBOL_STR(usbnet_get_msglevel) },
	{ 0x632e0286, __VMLINUX_SYMBOL_STR(usbnet_get_drvinfo) },
	{ 0x6ff41f85, __VMLINUX_SYMBOL_STR(usbnet_get_stats64) },
	{ 0x31a2b829, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x47e76171, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x2f2cec8d, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x5c61cfec, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xbe82ee28, __VMLINUX_SYMBOL_STR(of_get_mac_address) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x80698041, __VMLINUX_SYMBOL_STR(usbnet_get_endpoints) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x12936d6e, __VMLINUX_SYMBOL_STR(mii_nway_restart) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x9b017e86, __VMLINUX_SYMBOL_STR(usbnet_defer_kevent) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x66996915, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x901e1532, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x75d0802d, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x1834ff91, __VMLINUX_SYMBOL_STR(usbnet_change_mtu) },
	{ 0x3e7cae92, __VMLINUX_SYMBOL_STR(mii_ethtool_gset) },
	{ 0xf24549f, __VMLINUX_SYMBOL_STR(mii_check_media) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x315988ca, __VMLINUX_SYMBOL_STR(usbnet_read_cmd_nopm) },
	{ 0x6e76c51f, __VMLINUX_SYMBOL_STR(usbnet_read_cmd) },
	{ 0x907ea076, __VMLINUX_SYMBOL_STR(usbnet_write_cmd_nopm) },
	{ 0x705a2d01, __VMLINUX_SYMBOL_STR(usbnet_write_cmd) },
	{ 0x542a3c2e, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0xc1ed1633, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x8ffdb3b8, __VMLINUX_SYMBOL_STR(crc16) },
	{ 0x9fb633d5, __VMLINUX_SYMBOL_STR(generic_mii_ioctl) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x6220b4a2, __VMLINUX_SYMBOL_STR(crc32_le) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x99ab9445, __VMLINUX_SYMBOL_STR(__dev_kfree_skb_any) },
	{ 0xf4c95eee, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0424p7500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0424p7505d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "EE2D61CF35DBF0436B58E9D");
