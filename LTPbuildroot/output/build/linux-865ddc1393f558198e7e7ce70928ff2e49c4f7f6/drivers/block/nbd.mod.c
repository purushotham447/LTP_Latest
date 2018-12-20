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
	{ 0xfffae983, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xe492077d, __VMLINUX_SYMBOL_STR(genl_unregister_family) },
	{ 0xd6387855, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x7d45df8, __VMLINUX_SYMBOL_STR(genl_register_family) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xa8344bad, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x9850203e, __VMLINUX_SYMBOL_STR(blk_mq_tag_to_rq) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x21f032fe, __VMLINUX_SYMBOL_STR(iov_iter_advance) },
	{ 0xc65e700a, __VMLINUX_SYMBOL_STR(iov_iter_bvec) },
	{ 0x18047ebe, __VMLINUX_SYMBOL_STR(blk_mq_unique_tag) },
	{ 0x689e06e, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xce6db0ea, __VMLINUX_SYMBOL_STR(blk_mq_start_request) },
	{ 0x3afca61a, __VMLINUX_SYMBOL_STR(blk_mq_requeue_request) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xd6229f95, __VMLINUX_SYMBOL_STR(blkdev_reread_part) },
	{ 0x5b19634d, __VMLINUX_SYMBOL_STR(div_s64_rem) },
	{ 0xbc0f1831, __VMLINUX_SYMBOL_STR(kill_bdev) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x5fe298b2, __VMLINUX_SYMBOL_STR(bd_set_size) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xf1deabf2, __VMLINUX_SYMBOL_STR(div64_u64) },
	{ 0x9610ef1f, __VMLINUX_SYMBOL_STR(blk_queue_physical_block_size) },
	{ 0xed63fa6b, __VMLINUX_SYMBOL_STR(blk_queue_logical_block_size) },
	{ 0xff6e7c7e, __VMLINUX_SYMBOL_STR(debugfs_create_u32) },
	{ 0xdcc7462f, __VMLINUX_SYMBOL_STR(debugfs_create_u64) },
	{ 0x2c346f30, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x6f7f1a6f, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x49e47a, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0x1126f883, __VMLINUX_SYMBOL_STR(blk_queue_write_cache) },
	{ 0x337a2a75, __VMLINUX_SYMBOL_STR(set_disk_ro) },
	{ 0xb1202761, __VMLINUX_SYMBOL_STR(blk_mq_update_nr_hw_queues) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xb33ccf56, __VMLINUX_SYMBOL_STR(sk_set_memalloc) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf5fbdea6, __VMLINUX_SYMBOL_STR(blk_queue_rq_timeout) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0x15b3ba88, __VMLINUX_SYMBOL_STR(netlink_capable) },
	{ 0x20de0eac, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x22a6579e, __VMLINUX_SYMBOL_STR(blk_mq_unquiesce_queue) },
	{ 0xeea45404, __VMLINUX_SYMBOL_STR(blk_mq_tagset_busy_iter) },
	{ 0x255f3925, __VMLINUX_SYMBOL_STR(blk_mq_quiesce_queue) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xbfb4486c, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x60ceba45, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x55555e79, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xf0e0a296, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0xf5a03b27, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0x6ca9db54, __VMLINUX_SYMBOL_STR(refcount_dec_and_mutex_lock) },
	{ 0x38c9d41c, __VMLINUX_SYMBOL_STR(radix_tree_delete_item) },
	{ 0x95f17c15, __VMLINUX_SYMBOL_STR(blk_mq_free_tag_set) },
	{ 0x154c7db9, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x6282e515, __VMLINUX_SYMBOL_STR(device_add_disk) },
	{ 0x70752a38, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0x29f7e4d2, __VMLINUX_SYMBOL_STR(blk_queue_max_segments) },
	{ 0x646c8a8c, __VMLINUX_SYMBOL_STR(blk_queue_max_segment_size) },
	{ 0x88a6ee07, __VMLINUX_SYMBOL_STR(blk_queue_max_discard_sectors) },
	{ 0xd27baf97, __VMLINUX_SYMBOL_STR(blk_mq_init_queue) },
	{ 0xfd777325, __VMLINUX_SYMBOL_STR(blk_mq_alloc_tag_set) },
	{ 0x93bf7c0e, __VMLINUX_SYMBOL_STR(idr_alloc_cmn) },
	{ 0x34f80151, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x9ebc1ca9, __VMLINUX_SYMBOL_STR(blk_mq_end_request) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xf92ed216, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xb859f38b, __VMLINUX_SYMBOL_STR(krealloc) },
	{ 0xed874ab8, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe7cd355, __VMLINUX_SYMBOL_STR(netlink_broadcast) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xbf5cc4cb, __VMLINUX_SYMBOL_STR(iov_iter_kvec) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x1f95fdd4, __VMLINUX_SYMBOL_STR(sock_recvmsg) },
	{ 0x8ccaa01c, __VMLINUX_SYMBOL_STR(sock_sendmsg) },
	{ 0xfbbc4e37, __VMLINUX_SYMBOL_STR(blk_mq_complete_request) },
	{ 0xc5c891ee, __VMLINUX_SYMBOL_STR(blk_mq_request_started) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x699669c1, __VMLINUX_SYMBOL_STR(idr_for_each) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x4124ced2, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0xb86d6479, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0xedd7e40b, __VMLINUX_SYMBOL_STR(genlmsg_put) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F8504F95103BB66D10CBE33");
