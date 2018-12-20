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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe56a9336, __VMLINUX_SYMBOL_STR(snd_pcm_format_width) },
	{ 0xb362d4bb, __VMLINUX_SYMBOL_STR(vchi_msg_dequeue) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xe5b5d651, __VMLINUX_SYMBOL_STR(vchi_bulk_queue_transmit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x47b628d, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_step) },
	{ 0xbe6d3e2e, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0x686df339, __VMLINUX_SYMBOL_STR(vchi_initialise) },
	{ 0xf227e770, __VMLINUX_SYMBOL_STR(vchi_service_open) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xe93e49c3, __VMLINUX_SYMBOL_STR(devres_free) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x45a172d0, __VMLINUX_SYMBOL_STR(vchi_queue_kernel_message) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x19465956, __VMLINUX_SYMBOL_STR(devres_alloc_node) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x73be3770, __VMLINUX_SYMBOL_STR(vchi_service_use) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xa8344bad, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8df22a32, __VMLINUX_SYMBOL_STR(snd_device_new) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x6c49fc55, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16b19dbb, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0x3ca7dbcc, __VMLINUX_SYMBOL_STR(vchi_connect) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x5fb57b74, __VMLINUX_SYMBOL_STR(snd_pcm_lib_free_pages) },
	{ 0xc009e8c2, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0x2f670f3d, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xab52feee, __VMLINUX_SYMBOL_STR(snd_pcm_lib_malloc_pages) },
	{ 0x48244456, __VMLINUX_SYMBOL_STR(vchi_service_close) },
	{ 0xde7f6d09, __VMLINUX_SYMBOL_STR(snd_card_new) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xed7fe89b, __VMLINUX_SYMBOL_STR(snd_ctl_new1) },
	{ 0x2394bc74, __VMLINUX_SYMBOL_STR(vchi_service_release) },
	{ 0x588913b2, __VMLINUX_SYMBOL_STR(devres_add) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xaf10d009, __VMLINUX_SYMBOL_STR(vchi_get_peer_version) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x23fa0429, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0xf6e6c64b, __VMLINUX_SYMBOL_STR(snd_pcm_lib_preallocate_pages_for_all) },
	{ 0x72f4eb3d, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xbe2701cc, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x97faf372, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x689e06e, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xccf3e878, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x8e49e81b, __VMLINUX_SYMBOL_STR(snd_ctl_add) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x39e0d40b, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-pcm,snd";

MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-audio");
MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-audioC*");

MODULE_INFO(srcversion, "E5D598E47E3BA0AA5049F39");
