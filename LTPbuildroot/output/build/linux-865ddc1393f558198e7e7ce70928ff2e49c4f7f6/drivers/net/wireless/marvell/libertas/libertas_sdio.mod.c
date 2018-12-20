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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x13cae825, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xd83a9cbd, __VMLINUX_SYMBOL_STR(lbs_resume) },
	{ 0x9528dbeb, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0xc5bc2853, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x2f2a6c42, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x9b20172f, __VMLINUX_SYMBOL_STR(lbs_stop_card) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xa7b0b48, __VMLINUX_SYMBOL_STR(netdev_alert) },
	{ 0xb2cfa2c8, __VMLINUX_SYMBOL_STR(__lbs_cmd) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x4c7d44cb, __VMLINUX_SYMBOL_STR(sdio_get_host_pm_caps) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x418e630e, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x4c8b7c0, __VMLINUX_SYMBOL_STR(lbs_start_card) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x1106ae55, __VMLINUX_SYMBOL_STR(lbs_queue_event) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xcef5379d, __VMLINUX_SYMBOL_STR(lbs_get_firmware_async) },
	{ 0xc2a1acaf, __VMLINUX_SYMBOL_STR(lbs_cmd_copyback) },
	{ 0xee660c27, __VMLINUX_SYMBOL_STR(lbs_suspend) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xb39bf7e4, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xa24e7282, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0xa9c51fb7, __VMLINUX_SYMBOL_STR(lbs_remove_card) },
	{ 0x5bf9c3ef, __VMLINUX_SYMBOL_STR(sdio_f0_writeb) },
	{ 0xc8a448eb, __VMLINUX_SYMBOL_STR(sdio_set_host_pm_flags) },
	{ 0x9bb67760, __VMLINUX_SYMBOL_STR(lbs_process_rxed_packet) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x151bcbc9, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0x608f2d2a, __VMLINUX_SYMBOL_STR(lbs_host_to_card_done) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x8b8714d, __VMLINUX_SYMBOL_STR(sdio_align_size) },
	{ 0x4409df7d, __VMLINUX_SYMBOL_STR(lbs_add_card) },
	{ 0xdede32e8, __VMLINUX_SYMBOL_STR(sdio_f0_readb) },
	{ 0xc78947ae, __VMLINUX_SYMBOL_STR(mmc_add_host) },
	{ 0xf89661b1, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x314af749, __VMLINUX_SYMBOL_STR(mmc_remove_host) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x29012166, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0xc97fbcbd, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x3782dfe5, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x14e07511, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x6ae54aee, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0xec525682, __VMLINUX_SYMBOL_STR(lbs_notify_command_response) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libertas";

MODULE_ALIAS("sdio:c*v02DFd9103*");
MODULE_ALIAS("sdio:c*v02DFd9104*");

MODULE_INFO(srcversion, "7314028460BA914DB1FAF23");
