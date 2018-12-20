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
	{ 0x882e57e5, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x66996915, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x75d0802d, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0xca90ff30, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xfd72abf8, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x25da5053, __VMLINUX_SYMBOL_STR(rndis_tx_fixup) },
	{ 0x85e24731, __VMLINUX_SYMBOL_STR(rndis_rx_fixup) },
	{ 0xe826d8c1, __VMLINUX_SYMBOL_STR(rndis_status) },
	{ 0x6ff41f85, __VMLINUX_SYMBOL_STR(usbnet_get_stats64) },
	{ 0x31a2b829, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0x1d5df4f0, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x7936fcb1, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x47e76171, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x2f2cec8d, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x5c61cfec, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xb859f38b, __VMLINUX_SYMBOL_STR(krealloc) },
	{ 0xedd8f28e, __VMLINUX_SYMBOL_STR(wiphy_register) },
	{ 0x1fbbe095, __VMLINUX_SYMBOL_STR(generic_rndis_bind) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xe3dead2e, __VMLINUX_SYMBOL_STR(wiphy_new_nm) },
	{ 0xf89661b1, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x304a4ca, __VMLINUX_SYMBOL_STR(usbnet_purge_paused_rxq) },
	{ 0x9c64fbd, __VMLINUX_SYMBOL_STR(ieee80211_frequency_to_channel) },
	{ 0xe8663ae6, __VMLINUX_SYMBOL_STR(ieee80211_channel_to_frequency) },
	{ 0x8bbdb26d, __VMLINUX_SYMBOL_STR(cfg80211_cqm_rssi_notify) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x98134cfb, __VMLINUX_SYMBOL_STR(cfg80211_roamed) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc09d4b2a, __VMLINUX_SYMBOL_STR(cfg80211_connect_done) },
	{ 0xfd397c86, __VMLINUX_SYMBOL_STR(cfg80211_disconnected) },
	{ 0xd6d7cce4, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0xdfd68da, __VMLINUX_SYMBOL_STR(usbnet_resume_rx) },
	{ 0xcb2853d, __VMLINUX_SYMBOL_STR(cfg80211_ibss_joined) },
	{ 0xcdd58911, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x72c460e2, __VMLINUX_SYMBOL_STR(wiphy_free) },
	{ 0x6bbb3fc7, __VMLINUX_SYMBOL_STR(wiphy_unregister) },
	{ 0xdbfe1346, __VMLINUX_SYMBOL_STR(rndis_unbind) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x1eb9516e, __VMLINUX_SYMBOL_STR(round_jiffies_relative) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xfd792e2a, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x58d2273e, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xaab91aae, __VMLINUX_SYMBOL_STR(cfg80211_scan_done) },
	{ 0x9fd8746f, __VMLINUX_SYMBOL_STR(cfg80211_put_bss) },
	{ 0x9278bcfb, __VMLINUX_SYMBOL_STR(cfg80211_inform_bss_data) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xa7453a2c, __VMLINUX_SYMBOL_STR(ieee80211_get_channel) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x542a3c2e, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8a913a2c, __VMLINUX_SYMBOL_STR(rndis_command) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0xfea325fc, __VMLINUX_SYMBOL_STR(cfg80211_michael_mic_failure) },
	{ 0x414d9543, __VMLINUX_SYMBOL_STR(cfg80211_pmksa_candidate_notify) },
	{ 0x579e79a8, __VMLINUX_SYMBOL_STR(usbnet_pause_rx) },
	{ 0x901e1532, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rndis_host,cfg80211";

MODULE_ALIAS("usb:v0411p00BCd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0BAFp011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v050Dp011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v1799p011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p0014d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p0026d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0B05p1717d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0A5CpD11Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v1690p0715d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p000Ed*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0BAFp0111d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0411p004Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*icEFisc01ip01in*");

MODULE_INFO(srcversion, "B3DC2365F94786A625636B4");
