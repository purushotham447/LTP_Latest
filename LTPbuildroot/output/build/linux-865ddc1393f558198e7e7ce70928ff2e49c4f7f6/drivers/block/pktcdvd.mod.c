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
	{ 0xd1ae5f77, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0xd9eb8ddc, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x4c25efff, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0xf4a9e9e7, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0xad050f2b, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xc6486daf, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0x1e83ff34, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x1e445ab7, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x51cb7df0, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xc90407b2, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x5fe298b2, __VMLINUX_SYMBOL_STR(bd_set_size) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x1920a67f, __VMLINUX_SYMBOL_STR(__blkdev_driver_ioctl) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x67bf9f54, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xd2e9487e, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0x2e053047, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0x899d87d4, __VMLINUX_SYMBOL_STR(bio_copy_data) },
	{ 0x59ad0162, __VMLINUX_SYMBOL_STR(clear_wb_congested) },
	{ 0x10ed43f0, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0x4a69ceea, __VMLINUX_SYMBOL_STR(set_user_nice) },
	{ 0xaad8c7d6, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x2c346f30, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x6f7f1a6f, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x64c3e13e, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x6282e515, __VMLINUX_SYMBOL_STR(device_add_disk) },
	{ 0x5f487a65, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xf4bfa21, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x27168320, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x70752a38, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0xed63fa6b, __VMLINUX_SYMBOL_STR(blk_queue_logical_block_size) },
	{ 0x21970f08, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0x9ac6ea7e, __VMLINUX_SYMBOL_STR(set_blocksize) },
	{ 0x2492d879, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0x410aefa8, __VMLINUX_SYMBOL_STR(blkdev_get) },
	{ 0xfa9cad3, __VMLINUX_SYMBOL_STR(bdget) },
	{ 0x8f5ecd7c, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x34f80151, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe1dff2d, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xd5b03b51, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x154c7db9, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0xf0e0a296, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0xf5a03b27, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xab0b7645, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0xbe2701cc, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x6dec5a3e, __VMLINUX_SYMBOL_STR(debugfs_remove) },
	{ 0xf14c5dcc, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x4e251c31, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xbfb4486c, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0xa4922285, __VMLINUX_SYMBOL_STR(kobject_init_and_add) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x6b1b67d3, __VMLINUX_SYMBOL_STR(__bdevname) },
	{ 0x938999db, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa53012, __VMLINUX_SYMBOL_STR(bio_clone_fast) },
	{ 0x64999478, __VMLINUX_SYMBOL_STR(congestion_wait) },
	{ 0x8b8bef84, __VMLINUX_SYMBOL_STR(set_wb_congested) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0xbda2195, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xb869ebfe, __VMLINUX_SYMBOL_STR(bio_chain) },
	{ 0xcfe0785a, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0xafeba97b, __VMLINUX_SYMBOL_STR(blk_queue_split) },
	{ 0xd51852ab, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0xc368ae24, __VMLINUX_SYMBOL_STR(bio_reset) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xca9360b5, __VMLINUX_SYMBOL_STR(rb_next) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x7958f0b5, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xbac2cb51, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x4f476e96, __VMLINUX_SYMBOL_STR(init_cdrom_command) },
	{ 0x2d44ddd4, __VMLINUX_SYMBOL_STR(blk_put_request) },
	{ 0x9b931c28, __VMLINUX_SYMBOL_STR(blk_execute_rq) },
	{ 0x334da4e, __VMLINUX_SYMBOL_STR(scsi_command_size_tbl) },
	{ 0x4bd03777, __VMLINUX_SYMBOL_STR(blk_rq_map_kern) },
	{ 0xd460f989, __VMLINUX_SYMBOL_STR(blk_get_request) },
	{ 0x44b5ee9a, __VMLINUX_SYMBOL_STR(kasprintf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cdrom";


MODULE_INFO(srcversion, "16C3A7A012864F13F67F083");
