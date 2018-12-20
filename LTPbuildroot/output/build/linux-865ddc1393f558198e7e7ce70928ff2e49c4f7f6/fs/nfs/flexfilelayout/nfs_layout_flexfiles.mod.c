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
	{ 0xd84bd47f, __VMLINUX_SYMBOL_STR(nfs4_schedule_session_recovery) },
	{ 0x3397947f, __VMLINUX_SYMBOL_STR(pnfs_nfs_generic_sync) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xaa305f67, __VMLINUX_SYMBOL_STR(xdr_init_encode) },
	{ 0xd391bcc9, __VMLINUX_SYMBOL_STR(nfs4_pnfs_ds_connect) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x96ab9502, __VMLINUX_SYMBOL_STR(pnfs_generic_clear_request_commit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xcdc256df, __VMLINUX_SYMBOL_STR(nfs4_setup_sequence) },
	{ 0x679489ee, __VMLINUX_SYMBOL_STR(nfs_init_cinfo) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0xaf6fa4c4, __VMLINUX_SYMBOL_STR(nfs_initiate_commit) },
	{ 0x15e55f49, __VMLINUX_SYMBOL_STR(pnfs_error_mark_layout_for_return) },
	{ 0x5b8475c1, __VMLINUX_SYMBOL_STR(nfs4_pnfs_ds_put) },
	{ 0x48d3f107, __VMLINUX_SYMBOL_STR(put_rpccred) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x54bef45, __VMLINUX_SYMBOL_STR(layoutstats_timer) },
	{ 0x316e70e, __VMLINUX_SYMBOL_STR(nfs4_delete_deviceid) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x6833b73d, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0x643d9ba1, __VMLINUX_SYMBOL_STR(groups_free) },
	{ 0x7ef01af9, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_commit_ds) },
	{ 0x6620f197, __VMLINUX_SYMBOL_STR(nfs4_decode_mp_ds_addr) },
	{ 0x9224de6c, __VMLINUX_SYMBOL_STR(nfs_initiate_pgio) },
	{ 0xdac6cebe, __VMLINUX_SYMBOL_STR(nfs4_set_rw_stateid) },
	{ 0xcb01c75c, __VMLINUX_SYMBOL_STR(pnfs_generic_commit_pagelist) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x968db776, __VMLINUX_SYMBOL_STR(pnfs_generic_recover_commit_reqs) },
	{ 0x7a234010, __VMLINUX_SYMBOL_STR(nfs4_sequence_done) },
	{ 0xba430d86, __VMLINUX_SYMBOL_STR(xdr_reserve_space) },
	{ 0x17214a20, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_test) },
	{ 0x4be1f1a5, __VMLINUX_SYMBOL_STR(pnfs_update_layout) },
	{ 0x305a3e4e, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0xf0742f25, __VMLINUX_SYMBOL_STR(rpc_exit) },
	{ 0xca256c15, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_cleanup) },
	{ 0xbc808ebe, __VMLINUX_SYMBOL_STR(pnfs_generic_write_commit_done) },
	{ 0xe938801d, __VMLINUX_SYMBOL_STR(rpc_delay) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xe952a75f, __VMLINUX_SYMBOL_STR(pnfs_generic_layout_insert_lseg) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3a970763, __VMLINUX_SYMBOL_STR(xdr_init_decode_pages) },
	{ 0xbac3cbf2, __VMLINUX_SYMBOL_STR(ns_to_timespec64) },
	{ 0x5f84e6d4, __VMLINUX_SYMBOL_STR(rpc_call_start) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0x3facc410, __VMLINUX_SYMBOL_STR(pnfs_read_resend_pnfs) },
	{ 0x40701e3e, __VMLINUX_SYMBOL_STR(nfs4_find_get_deviceid) },
	{ 0x4957b2b0, __VMLINUX_SYMBOL_STR(nfs4_find_or_create_ds_client) },
	{ 0xeb725d71, __VMLINUX_SYMBOL_STR(rpc_max_payload) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x1c35bb11, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_write_mds) },
	{ 0x2fd763e3, __VMLINUX_SYMBOL_STR(pnfs_layout_mark_request_commit) },
	{ 0x17e30d4a, __VMLINUX_SYMBOL_STR(pnfs_destroy_layout) },
	{ 0xdb0aa553, __VMLINUX_SYMBOL_STR(nfs4_pnfs_ds_add) },
	{ 0x84b8228a, __VMLINUX_SYMBOL_STR(pnfs_layoutcommit_inode) },
	{ 0x980caf71, __VMLINUX_SYMBOL_STR(pnfs_put_lseg) },
	{ 0xef8b4a57, __VMLINUX_SYMBOL_STR(nfs4_put_deviceid_node) },
	{ 0xf407d46d, __VMLINUX_SYMBOL_STR(pnfs_set_layoutcommit) },
	{ 0x8350fb27, __VMLINUX_SYMBOL_STR(pnfs_generic_scan_commit_lists) },
	{ 0x69d3558d, __VMLINUX_SYMBOL_STR(pnfs_generic_rw_release) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xba8bb333, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0xa7116397, __VMLINUX_SYMBOL_STR(nfs4_test_deviceid_unavailable) },
	{ 0xa02df320, __VMLINUX_SYMBOL_STR(nfs_map_string_to_numeric) },
	{ 0xf999267e, __VMLINUX_SYMBOL_STR(pnfs_generic_commit_release) },
	{ 0xca238501, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_readpages) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x65994f1, __VMLINUX_SYMBOL_STR(xdr_encode_opaque_fixed) },
	{ 0x704e8e22, __VMLINUX_SYMBOL_STR(pnfs_read_done_resend_to_mds) },
	{ 0xe5919cb1, __VMLINUX_SYMBOL_STR(xdr_encode_opaque) },
	{ 0xf4d74125, __VMLINUX_SYMBOL_STR(rpc_restart_call_prepare) },
	{ 0x3e2b0ba6, __VMLINUX_SYMBOL_STR(groups_alloc) },
	{ 0x498c4272, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_writepages) },
	{ 0x19afcad5, __VMLINUX_SYMBOL_STR(pnfs_generic_prepare_to_resend_writes) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x8607304, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_check_layout) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe156d165, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_read) },
	{ 0x385d5a60, __VMLINUX_SYMBOL_STR(pnfs_write_done_resend_to_mds) },
	{ 0x1640a25f, __VMLINUX_SYMBOL_STR(rpc_wake_up) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x358c6e3, __VMLINUX_SYMBOL_STR(rpc_count_iostats_metrics) },
	{ 0xa7fcedd8, __VMLINUX_SYMBOL_STR(xdr_inline_decode) },
	{ 0x2c4e6bd, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_write) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x552d4588, __VMLINUX_SYMBOL_STR(rpc_lookup_generic_cred) },
	{ 0x2c93f6a5, __VMLINUX_SYMBOL_STR(xdr_write_pages) },
	{ 0x82a1fb09, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_read_mds) },
	{ 0x90ed0fa, __VMLINUX_SYMBOL_STR(nfs4_init_deviceid_node) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xdd828e7a, __VMLINUX_SYMBOL_STR(xdr_set_scratch_buffer) },
	{ 0xd826a162, __VMLINUX_SYMBOL_STR(nfs_writeback_update_inode) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0x6639c423, __VMLINUX_SYMBOL_STR(pnfs_register_layoutdriver) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "46877C81D8018617731BD08");
