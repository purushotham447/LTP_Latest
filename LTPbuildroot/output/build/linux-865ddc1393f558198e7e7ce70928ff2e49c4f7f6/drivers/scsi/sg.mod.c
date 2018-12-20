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
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xd9eb8ddc, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xd6387855, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0xeef35166, __VMLINUX_SYMBOL_STR(class_interface_unregister) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xad050f2b, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xf3b8967a, __VMLINUX_SYMBOL_STR(scsi_register_interface) },
	{ 0x65961174, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xd8e484f0, __VMLINUX_SYMBOL_STR(register_chrdev_region) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x334da4e, __VMLINUX_SYMBOL_STR(scsi_command_size_tbl) },
	{ 0x41fed593, __VMLINUX_SYMBOL_STR(sg_scsi_ioctl) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0xb5c00014, __VMLINUX_SYMBOL_STR(_raw_write_lock_irq) },
	{ 0x9486966c, __VMLINUX_SYMBOL_STR(blk_trace_startstop) },
	{ 0xaca4ef9, __VMLINUX_SYMBOL_STR(blk_trace_setup) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xf1123767, __VMLINUX_SYMBOL_STR(blk_trace_remove) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xf920413b, __VMLINUX_SYMBOL_STR(scsi_ioctl) },
	{ 0xf33b819d, __VMLINUX_SYMBOL_STR(scsi_ioctl_block_when_processing_errors) },
	{ 0xf5eb86ea, __VMLINUX_SYMBOL_STR(blk_verify_command) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x596bca8, __VMLINUX_SYMBOL_STR(blk_rq_map_user_iov) },
	{ 0xa96d0a05, __VMLINUX_SYMBOL_STR(blk_end_request_all) },
	{ 0x708ecc91, __VMLINUX_SYMBOL_STR(blk_rq_map_user) },
	{ 0x5f0fbd68, __VMLINUX_SYMBOL_STR(blk_execute_rq_nowait) },
	{ 0xe20d535a, __VMLINUX_SYMBOL_STR(import_iovec) },
	{ 0xd460f989, __VMLINUX_SYMBOL_STR(blk_get_request) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x2d44ddd4, __VMLINUX_SYMBOL_STR(blk_put_request) },
	{ 0xee3659b, __VMLINUX_SYMBOL_STR(blk_rq_unmap_user) },
	{ 0x2492d879, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xf7f7ab8b, __VMLINUX_SYMBOL_STR(scsi_device_put) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xa1978a24, __VMLINUX_SYMBOL_STR(scsi_block_when_processing_errors) },
	{ 0xc932afdc, __VMLINUX_SYMBOL_STR(scsi_autopm_get_device) },
	{ 0x7c3ec630, __VMLINUX_SYMBOL_STR(scsi_device_get) },
	{ 0xb86d6479, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0xd1ae5f77, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x6bbda04a, __VMLINUX_SYMBOL_STR(sdev_prefix_printk) },
	{ 0x40439a23, __VMLINUX_SYMBOL_STR(sysfs_create_link) },
	{ 0x64c3e13e, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x67e64e02, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x93bf7c0e, __VMLINUX_SYMBOL_STR(idr_alloc_cmn) },
	{ 0x84ffea8b, __VMLINUX_SYMBOL_STR(idr_preload) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x9ea73f87, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x34f80151, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x7213a1b4, __VMLINUX_SYMBOL_STR(__scsi_print_sense) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb7488905, __VMLINUX_SYMBOL_STR(scsi_normalize_sense) },
	{ 0x69035f, __VMLINUX_SYMBOL_STR(__blk_put_request) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x82cd602c, __VMLINUX_SYMBOL_STR(scsi_autopm_put_device) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x9beb535e, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0x4ffb44fd, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x57e8006b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x38bbb804, __VMLINUX_SYMBOL_STR(sysfs_remove_link) },
	{ 0xb9fa3b47, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x154c7db9, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x38c9d41c, __VMLINUX_SYMBOL_STR(radix_tree_delete_item) },
	{ 0xceed7f85, __VMLINUX_SYMBOL_STR(_raw_write_unlock_irqrestore) },
	{ 0x97ec1ff, __VMLINUX_SYMBOL_STR(_raw_write_lock_irqsave) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9cba3c37, __VMLINUX_SYMBOL_STR(_raw_read_unlock_irqrestore) },
	{ 0xe1f0ab3a, __VMLINUX_SYMBOL_STR(_raw_read_lock_irqsave) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "297D1451DFC7A45E9CA62CB");
