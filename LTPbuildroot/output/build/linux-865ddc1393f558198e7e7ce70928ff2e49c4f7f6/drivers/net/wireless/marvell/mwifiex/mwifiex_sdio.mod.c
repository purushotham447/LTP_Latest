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
	{ 0x3640667f, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0x6082fd21, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfed19a97, __VMLINUX_SYMBOL_STR(mwifiex_cancel_hs) },
	{ 0x9528dbeb, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0xc5bc2853, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x2f2a6c42, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0xf21d3deb, __VMLINUX_SYMBOL_STR(mmc_hw_reset) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xf880a8cd, __VMLINUX_SYMBOL_STR(mwifiex_disable_auto_ds) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x99ab9445, __VMLINUX_SYMBOL_STR(__dev_kfree_skb_any) },
	{ 0x398e8f87, __VMLINUX_SYMBOL_STR(mwifiex_process_sleep_confirm_resp) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x7349ce80, __VMLINUX_SYMBOL_STR(mwifiex_main_process) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x4c7d44cb, __VMLINUX_SYMBOL_STR(sdio_get_host_pm_caps) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xa8c95712, __VMLINUX_SYMBOL_STR(_mwifiex_dbg) },
	{ 0xa8344bad, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xc369eb79, __VMLINUX_SYMBOL_STR(mwifiex_add_card) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71caaac6, __VMLINUX_SYMBOL_STR(of_match_node) },
	{ 0x7c94d25, __VMLINUX_SYMBOL_STR(mwifiex_shutdown_sw) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x31bd9748, __VMLINUX_SYMBOL_STR(mwifiex_alloc_dma_align_buf) },
	{ 0xb39bf7e4, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xa24e7282, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0xc8a448eb, __VMLINUX_SYMBOL_STR(sdio_set_host_pm_flags) },
	{ 0xeaf594c1, __VMLINUX_SYMBOL_STR(mwifiex_dnld_fw) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x151bcbc9, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0xdede32e8, __VMLINUX_SYMBOL_STR(sdio_f0_readb) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xae966e88, __VMLINUX_SYMBOL_STR(mwifiex_reinit_sw) },
	{ 0x72b48ad2, __VMLINUX_SYMBOL_STR(mwifiex_handle_rx_packet) },
	{ 0x73fcf683, __VMLINUX_SYMBOL_STR(mwifiex_deauthenticate_all) },
	{ 0x1361da6a, __VMLINUX_SYMBOL_STR(mwifiex_remove_card) },
	{ 0xe9fe81e3, __VMLINUX_SYMBOL_STR(mwifiex_enable_hs) },
	{ 0xbd22b8fb, __VMLINUX_SYMBOL_STR(mwifiex_upload_device_dump) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x29012166, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0xc97fbcbd, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0xb7f4ee0a, __VMLINUX_SYMBOL_STR(mwifiex_drv_info_dump) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xfeeed6af, __VMLINUX_SYMBOL_STR(mwifiex_init_shutdown_fw) },
	{ 0x3782dfe5, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x14e07511, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x6ae54aee, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mwifiex";

MODULE_ALIAS("sdio:c*v02DFd9116*");
MODULE_ALIAS("sdio:c*v02DFd9119*");
MODULE_ALIAS("sdio:c*v02DFd9129*");
MODULE_ALIAS("sdio:c*v02DFd912D*");
MODULE_ALIAS("sdio:c*v02DFd9135*");
MODULE_ALIAS("sdio:c*v02DFd9139*");
MODULE_ALIAS("sdio:c*v02DFd9141*");

MODULE_INFO(srcversion, "A7D719B9B3E7392051E0DB1");
