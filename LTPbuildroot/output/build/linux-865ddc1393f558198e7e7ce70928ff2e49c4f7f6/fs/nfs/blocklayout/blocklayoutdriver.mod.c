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
	{ 0xf23707a3, __VMLINUX_SYMBOL_STR(pnfs_unregister_layoutdriver) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x59ccc80b, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_init_write) },
	{ 0xb7f15023, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xc90407b2, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0x28f26f00, __VMLINUX_SYMBOL_STR(page_cache_next_hole) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xaaa14361, __VMLINUX_SYMBOL_STR(nfs_dreq_bytes_left) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xaa03063b, __VMLINUX_SYMBOL_STR(rpc_unlink) },
	{ 0xb547f583, __VMLINUX_SYMBOL_STR(pnfs_ld_write_done) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xd77f126b, __VMLINUX_SYMBOL_STR(dput) },
	{ 0xc3a2be67, __VMLINUX_SYMBOL_STR(nfs_net_id) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x9dd850b4, __VMLINUX_SYMBOL_STR(rpc_mkpipe_data) },
	{ 0xe49b7766, __VMLINUX_SYMBOL_STR(rpc_mkpipe_dentry) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x17214a20, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_test) },
	{ 0x44b5ee9a, __VMLINUX_SYMBOL_STR(kasprintf) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0xf7df7378, __VMLINUX_SYMBOL_STR(rpc_get_sb_net) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xaad8c7d6, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xca256c15, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_cleanup) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x99cdf564, __VMLINUX_SYMBOL_STR(pnfs_generic_sync) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3a970763, __VMLINUX_SYMBOL_STR(xdr_init_decode_pages) },
	{ 0xdd9020d0, __VMLINUX_SYMBOL_STR(rpc_queue_upcall) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd51852ab, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x40701e3e, __VMLINUX_SYMBOL_STR(nfs4_find_get_deviceid) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0xa8faa37a, __VMLINUX_SYMBOL_STR(blkdev_get_by_path) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x1c35bb11, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_write_mds) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x4dd7a28e, __VMLINUX_SYMBOL_STR(rpc_d_lookup_sb) },
	{ 0x17663969, __VMLINUX_SYMBOL_STR(blkdev_get_by_dev) },
	{ 0x67bf9f54, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xef8b4a57, __VMLINUX_SYMBOL_STR(nfs4_put_deviceid_node) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x5f40ce68, __VMLINUX_SYMBOL_STR(rpc_pipe_generic_upcall) },
	{ 0xbbaec3ef, __VMLINUX_SYMBOL_STR(submit_bio) },
	{ 0xbd9074b1, __VMLINUX_SYMBOL_STR(blk_finish_plug) },
	{ 0x387e1639, __VMLINUX_SYMBOL_STR(rpc_pipefs_notifier_register) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x5d8ea536, __VMLINUX_SYMBOL_STR(rpc_destroy_pipe_data) },
	{ 0xab0b7645, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0xf82ec573, __VMLINUX_SYMBOL_STR(rb_prev) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x89290368, __VMLINUX_SYMBOL_STR(rpc_put_sb_net) },
	{ 0xca238501, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_readpages) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x65994f1, __VMLINUX_SYMBOL_STR(xdr_encode_opaque_fixed) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0xe5919cb1, __VMLINUX_SYMBOL_STR(xdr_encode_opaque) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x498c4272, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_writepages) },
	{ 0x28d6861d, __VMLINUX_SYMBOL_STR(__vmalloc) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xbed5a169, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_init_read) },
	{ 0x1db7dc40, __VMLINUX_SYMBOL_STR(pgprot_kernel) },
	{ 0xca9360b5, __VMLINUX_SYMBOL_STR(rb_next) },
	{ 0xb51a3724, __VMLINUX_SYMBOL_STR(rpc_pipefs_notifier_unregister) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xa7fcedd8, __VMLINUX_SYMBOL_STR(xdr_inline_decode) },
	{ 0x1399c287, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x82a1fb09, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_read_mds) },
	{ 0x90ed0fa, __VMLINUX_SYMBOL_STR(nfs4_init_deviceid_node) },
	{ 0x494ac0c3, __VMLINUX_SYMBOL_STR(pnfs_set_lo_fail) },
	{ 0x7d705738, __VMLINUX_SYMBOL_STR(blk_start_plug) },
	{ 0xdd828e7a, __VMLINUX_SYMBOL_STR(xdr_set_scratch_buffer) },
	{ 0x8d09056, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0xdc16d318, __VMLINUX_SYMBOL_STR(pnfs_ld_read_done) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x6639c423, __VMLINUX_SYMBOL_STR(pnfs_register_layoutdriver) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "19B8E6B6A6B8EB7265A1F7F");
