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
	{ 0x28e2cb20, __VMLINUX_SYMBOL_STR(unregister_md_personality) },
	{ 0x76605447, __VMLINUX_SYMBOL_STR(register_md_personality) },
	{ 0x6b1b67d3, __VMLINUX_SYMBOL_STR(__bdevname) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0x28482544, __VMLINUX_SYMBOL_STR(submit_bio_wait) },
	{ 0x27ba2ea7, __VMLINUX_SYMBOL_STR(bio_trim) },
	{ 0xcf3528ec, __VMLINUX_SYMBOL_STR(rdev_clear_badblocks) },
	{ 0x1c20f9b6, __VMLINUX_SYMBOL_STR(md_check_recovery) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xd0ab4b6f, __VMLINUX_SYMBOL_STR(sync_page_io) },
	{ 0x899d87d4, __VMLINUX_SYMBOL_STR(bio_copy_data) },
	{ 0xf07c6988, __VMLINUX_SYMBOL_STR(bio_alloc_mddev) },
	{ 0xeff73571, __VMLINUX_SYMBOL_STR(md_wait_for_blocked_rdev) },
	{ 0xd27b25dd, __VMLINUX_SYMBOL_STR(blk_check_plugged) },
	{ 0x287d73f4, __VMLINUX_SYMBOL_STR(bitmap_startwrite) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x3ee589e2, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0x6f5696fb, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x4d3c153f, __VMLINUX_SYMBOL_STR(sigprocmask) },
	{ 0xad73041f, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x2e50e113, __VMLINUX_SYMBOL_STR(md_write_start) },
	{ 0xd4b07b71, __VMLINUX_SYMBOL_STR(md_error) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xe2510397, __VMLINUX_SYMBOL_STR(md_allow_write) },
	{ 0x40439a23, __VMLINUX_SYMBOL_STR(sysfs_create_link) },
	{ 0x38bbb804, __VMLINUX_SYMBOL_STR(sysfs_remove_link) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xbd9074b1, __VMLINUX_SYMBOL_STR(blk_finish_plug) },
	{ 0x7d705738, __VMLINUX_SYMBOL_STR(blk_start_plug) },
	{ 0xfa496411, __VMLINUX_SYMBOL_STR(md_done_sync) },
	{ 0x78909096, __VMLINUX_SYMBOL_STR(md_unregister_thread) },
	{ 0xcf79de0a, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0xff4579e1, __VMLINUX_SYMBOL_STR(blk_queue_max_write_zeroes_sectors) },
	{ 0x9b59862b, __VMLINUX_SYMBOL_STR(blk_queue_max_write_same_sectors) },
	{ 0x1837ffd5, __VMLINUX_SYMBOL_STR(mddev_init_writes_pending) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x9e4d251, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0xe2eaa58b, __VMLINUX_SYMBOL_STR(md_integrity_add_rdev) },
	{ 0x9a2379af, __VMLINUX_SYMBOL_STR(kernfs_notify) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xc90407b2, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xd51852ab, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x151f4898, __VMLINUX_SYMBOL_STR(schedule_timeout_uninterruptible) },
	{ 0xa1250461, __VMLINUX_SYMBOL_STR(bitmap_end_sync) },
	{ 0x4a07d4d4, __VMLINUX_SYMBOL_STR(rdev_set_badblocks) },
	{ 0xc368ae24, __VMLINUX_SYMBOL_STR(bio_reset) },
	{ 0x425dc127, __VMLINUX_SYMBOL_STR(bitmap_cond_end_sync) },
	{ 0x46b24028, __VMLINUX_SYMBOL_STR(bitmap_start_sync) },
	{ 0x818c01dc, __VMLINUX_SYMBOL_STR(bitmap_close_sync) },
	{ 0x35c0dec1, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0x2ab9a0a4, __VMLINUX_SYMBOL_STR(bitmap_resize) },
	{ 0xdefa346c, __VMLINUX_SYMBOL_STR(md_register_thread) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0x1e83ff34, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0xd5b03b51, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x51cb7df0, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0xe1dff2d, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x650e4a99, __VMLINUX_SYMBOL_STR(__trace_note_message) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xbda2195, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xb869ebfe, __VMLINUX_SYMBOL_STR(bio_chain) },
	{ 0xcfe0785a, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0x36ba63a3, __VMLINUX_SYMBOL_STR(__tracepoint_block_bio_remap) },
	{ 0xa53012, __VMLINUX_SYMBOL_STR(bio_clone_fast) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x36040282, __VMLINUX_SYMBOL_STR(badblocks_check) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xe3ff1760, __VMLINUX_SYMBOL_STR(md_cluster_ops) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7958f0b5, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2fb2c9f0, __VMLINUX_SYMBOL_STR(md_wakeup_thread) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xd2e9487e, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x8484c4a3, __VMLINUX_SYMBOL_STR(bitmap_unplug) },
	{ 0x10ed43f0, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x938999db, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x5c0cc537, __VMLINUX_SYMBOL_STR(md_write_end) },
	{ 0x325142bb, __VMLINUX_SYMBOL_STR(bitmap_endwrite) },
	{ 0x67bf9f54, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0x2d0ce8d, __VMLINUX_SYMBOL_STR(bio_free_pages) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";


MODULE_INFO(srcversion, "F3870B6C3C32FC6B540C242");
