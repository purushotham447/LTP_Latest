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
	{ 0x854009ed, __VMLINUX_SYMBOL_STR(can_change_mtu) },
	{ 0x82b04bfc, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x6897ade, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x542a3c2e, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0x2a85a5d4, __VMLINUX_SYMBOL_STR(close_candev) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x1dfb2cdf, __VMLINUX_SYMBOL_STR(open_candev) },
	{ 0xc181fa7e, __VMLINUX_SYMBOL_STR(alloc_can_skb) },
	{ 0x3e72ef7b, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0xa9b5853b, __VMLINUX_SYMBOL_STR(alloc_can_err_skb) },
	{ 0x314e90da, __VMLINUX_SYMBOL_STR(netif_tx_wake_queue) },
	{ 0x8358b4a0, __VMLINUX_SYMBOL_STR(can_get_echo_skb) },
	{ 0xd230f88a, __VMLINUX_SYMBOL_STR(netif_device_detach) },
	{ 0x6cc84baa, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0xd6b14876, __VMLINUX_SYMBOL_STR(can_free_echo_skb) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xf1eccf6f, __VMLINUX_SYMBOL_STR(can_put_echo_skb) },
	{ 0x3bd2dceb, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x6ebc1f5f, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xf89661b1, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xfaf8f001, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x54b8b402, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x10d5b6b6, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x901e1532, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xf7dbebd5, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0xff8b720b, __VMLINUX_SYMBOL_STR(unregister_candev) },
	{ 0x71da3901, __VMLINUX_SYMBOL_STR(free_candev) },
	{ 0xe4b2a388, __VMLINUX_SYMBOL_STR(register_candev) },
	{ 0x58cde7ae, __VMLINUX_SYMBOL_STR(alloc_candev) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x26f02757, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can-dev";

MODULE_ALIAS("usb:v1D50p606Fd*dc*dsc*dp*ic*isc*ip*in00*");
MODULE_ALIAS("usb:v1209p2323d*dc*dsc*dp*ic*isc*ip*in00*");

MODULE_INFO(srcversion, "3CA8ECC7B17889CDB11879A");
