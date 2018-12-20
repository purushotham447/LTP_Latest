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
	{ 0xc35d0fbd, __VMLINUX_SYMBOL_STR(rt2x00usb_resume) },
	{ 0xe3bcdf40, __VMLINUX_SYMBOL_STR(rt2x00usb_suspend) },
	{ 0x84b77a4, __VMLINUX_SYMBOL_STR(rt2x00usb_disconnect) },
	{ 0xe2320eee, __VMLINUX_SYMBOL_STR(rt2x00mac_tx_frames_pending) },
	{ 0x8c05395a, __VMLINUX_SYMBOL_STR(rt2x00mac_get_ringparam) },
	{ 0xe61ba482, __VMLINUX_SYMBOL_STR(rt2x00mac_get_antenna) },
	{ 0xdddc4875, __VMLINUX_SYMBOL_STR(rt2x00mac_set_antenna) },
	{ 0xe62a8b5e, __VMLINUX_SYMBOL_STR(rt2x00mac_flush) },
	{ 0xf72494a4, __VMLINUX_SYMBOL_STR(rt2x00mac_rfkill_poll) },
	{ 0x1d050482, __VMLINUX_SYMBOL_STR(rt2x00mac_conf_tx) },
	{ 0xef187b21, __VMLINUX_SYMBOL_STR(rt2x00mac_get_stats) },
	{ 0xb152fdf5, __VMLINUX_SYMBOL_STR(rt2x00mac_sw_scan_complete) },
	{ 0xc476f250, __VMLINUX_SYMBOL_STR(rt2x00mac_sw_scan_start) },
	{ 0x3dcf4bd5, __VMLINUX_SYMBOL_STR(rt2x00mac_set_key) },
	{ 0x77cbe0c5, __VMLINUX_SYMBOL_STR(rt2x00mac_set_tim) },
	{ 0xf61c10b8, __VMLINUX_SYMBOL_STR(rt2x00mac_configure_filter) },
	{ 0xd409a19f, __VMLINUX_SYMBOL_STR(rt2x00mac_bss_info_changed) },
	{ 0x19ba65eb, __VMLINUX_SYMBOL_STR(rt2x00mac_config) },
	{ 0x7903c806, __VMLINUX_SYMBOL_STR(rt2x00mac_remove_interface) },
	{ 0x777ed583, __VMLINUX_SYMBOL_STR(rt2x00mac_add_interface) },
	{ 0xdefafd13, __VMLINUX_SYMBOL_STR(rt2x00mac_stop) },
	{ 0xce227fa, __VMLINUX_SYMBOL_STR(rt2x00mac_start) },
	{ 0xe3648673, __VMLINUX_SYMBOL_STR(rt2x00mac_tx) },
	{ 0xf6ab8df4, __VMLINUX_SYMBOL_STR(rt2x00usb_flush_queue) },
	{ 0x2be06b40, __VMLINUX_SYMBOL_STR(rt2x00usb_kick_queue) },
	{ 0xae5697c9, __VMLINUX_SYMBOL_STR(rt2x00usb_watchdog) },
	{ 0x1b561dbf, __VMLINUX_SYMBOL_STR(rt2x00usb_clear_entry) },
	{ 0x94ac9c46, __VMLINUX_SYMBOL_STR(rt2x00usb_uninitialize) },
	{ 0xd285d2c5, __VMLINUX_SYMBOL_STR(rt2x00usb_initialize) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xc460389a, __VMLINUX_SYMBOL_STR(rt2x00lib_set_mac_address) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x52067552, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_request) },
	{ 0x9a4ac43f, __VMLINUX_SYMBOL_STR(rt2x00usb_disable_radio) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x13d2211d, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_req_buff_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x69919d79, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_request_buff) },
	{ 0xaa93b990, __VMLINUX_SYMBOL_STR(rt2x00usb_probe) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rt2x00usb,rt2x00lib";

MODULE_ALIAS("usb:v0B05p1706d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p1707d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp7050d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp7051d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p000Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p001Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14B2p3C02d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3C00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p8001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p8007d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06F8pE000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p005Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0066d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0067d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p008Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0097d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6861d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6865d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6869d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp1706d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp2570d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp9020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v079Bp004Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0681p3C06d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0707pEE13d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v114Bp0110d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0769p11F3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0EB0p9020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F88p3012d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v5A57p0260d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "50526305F04672226A42A56");
