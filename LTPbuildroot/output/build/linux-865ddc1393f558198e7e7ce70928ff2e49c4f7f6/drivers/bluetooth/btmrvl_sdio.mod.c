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
	{ 0xa24e7282, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0x29012166, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2ebcd9e7, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x9f6efab6, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x3782dfe5, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x2f2a6c42, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x96ab8e0e, __VMLINUX_SYMBOL_STR(btmrvl_register_hdev) },
	{ 0x6ca87654, __VMLINUX_SYMBOL_STR(btmrvl_add_card) },
	{ 0x4acc6ca1, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0xaa076099, __VMLINUX_SYMBOL_STR(irq_of_parse_and_map) },
	{ 0x71caaac6, __VMLINUX_SYMBOL_STR(of_match_node) },
	{ 0xc5bc2853, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x3bc89987, __VMLINUX_SYMBOL_STR(btmrvl_send_module_cfg_cmd) },
	{ 0x67b3b7cf, __VMLINUX_SYMBOL_STR(btmrvl_remove_card) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x27bbf221, __VMLINUX_SYMBOL_STR(disable_irq_nosync) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x5e14aa80, __VMLINUX_SYMBOL_STR(btmrvl_interrupt) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9528dbeb, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x412ab0c8, __VMLINUX_SYMBOL_STR(btmrvl_check_evtpkt) },
	{ 0x317e9c3a, __VMLINUX_SYMBOL_STR(hci_recv_frame) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xbf5769ad, __VMLINUX_SYMBOL_STR(btmrvl_process_event) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xb39bf7e4, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x1165d124, __VMLINUX_SYMBOL_STR(dev_coredumpv) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0xd7442057, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0x6082fd21, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0xdede32e8, __VMLINUX_SYMBOL_STR(sdio_f0_readb) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x14e07511, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x151bcbc9, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0x6ae54aee, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0x3640667f, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0xc97fbcbd, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0xc8a448eb, __VMLINUX_SYMBOL_STR(sdio_set_host_pm_flags) },
	{ 0x7110b54a, __VMLINUX_SYMBOL_STR(btmrvl_enable_hs) },
	{ 0xa253b344, __VMLINUX_SYMBOL_STR(hci_suspend_dev) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x47022514, __VMLINUX_SYMBOL_STR(bt_err) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0xb55fb51, __VMLINUX_SYMBOL_STR(hci_resume_dev) },
	{ 0x4c7d44cb, __VMLINUX_SYMBOL_STR(sdio_get_host_pm_caps) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=btmrvl,bluetooth";

MODULE_ALIAS("sdio:c*v02DFd9105*");
MODULE_ALIAS("sdio:c*v02DFd911A*");
MODULE_ALIAS("sdio:c*v02DFd911B*");
MODULE_ALIAS("sdio:c*v02DFd912A*");
MODULE_ALIAS("sdio:c*v02DFd9136*");
MODULE_ALIAS("sdio:c*v02DFd912E*");
MODULE_ALIAS("sdio:c*v02DFd9142*");

MODULE_INFO(srcversion, "80BBCAD7DDF6F5DAF145531");
