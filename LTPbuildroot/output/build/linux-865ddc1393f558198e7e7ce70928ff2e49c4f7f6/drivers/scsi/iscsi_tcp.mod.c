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
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xc0358fe7, __VMLINUX_SYMBOL_STR(iscsi_session_recovery_timedout) },
	{ 0x2d65b83, __VMLINUX_SYMBOL_STR(iscsi_tcp_cleanup_task) },
	{ 0x1eb8391b, __VMLINUX_SYMBOL_STR(iscsi_tcp_task_xmit) },
	{ 0x3eb265dc, __VMLINUX_SYMBOL_STR(iscsi_tcp_task_init) },
	{ 0xfb7d536f, __VMLINUX_SYMBOL_STR(iscsi_conn_send_pdu) },
	{ 0x287c5496, __VMLINUX_SYMBOL_STR(iscsi_host_set_param) },
	{ 0x29539d62, __VMLINUX_SYMBOL_STR(iscsi_session_get_param) },
	{ 0x5aac06c, __VMLINUX_SYMBOL_STR(iscsi_conn_start) },
	{ 0x3e872c76, __VMLINUX_SYMBOL_STR(iscsi_eh_cmd_timed_out) },
	{ 0x72783d15, __VMLINUX_SYMBOL_STR(scsi_change_queue_depth) },
	{ 0xd3024715, __VMLINUX_SYMBOL_STR(iscsi_target_alloc) },
	{ 0xc97dc9ee, __VMLINUX_SYMBOL_STR(iscsi_eh_recover_target) },
	{ 0x340314bf, __VMLINUX_SYMBOL_STR(iscsi_eh_device_reset) },
	{ 0x361063ed, __VMLINUX_SYMBOL_STR(iscsi_eh_abort) },
	{ 0x54fff8d3, __VMLINUX_SYMBOL_STR(iscsi_queuecommand) },
	{ 0x76c85e1c, __VMLINUX_SYMBOL_STR(iscsi_unregister_transport) },
	{ 0x7d48f921, __VMLINUX_SYMBOL_STR(iscsi_register_transport) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x92ff9da6, __VMLINUX_SYMBOL_STR(blk_queue_dma_alignment) },
	{ 0xa412e273, __VMLINUX_SYMBOL_STR(blk_queue_bounce_limit) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc795326d, __VMLINUX_SYMBOL_STR(iscsi_tcp_r2tpool_alloc) },
	{ 0x297ec4ed, __VMLINUX_SYMBOL_STR(iscsi_session_setup) },
	{ 0x40cb2984, __VMLINUX_SYMBOL_STR(iscsi_host_add) },
	{ 0x1e267d25, __VMLINUX_SYMBOL_STR(iscsi_host_alloc) },
	{ 0x589ecbe5, __VMLINUX_SYMBOL_STR(iscsi_host_free) },
	{ 0xf8f67a5, __VMLINUX_SYMBOL_STR(iscsi_host_remove) },
	{ 0x4b99217a, __VMLINUX_SYMBOL_STR(iscsi_session_teardown) },
	{ 0xaa95efb5, __VMLINUX_SYMBOL_STR(iscsi_tcp_r2tpool_free) },
	{ 0x72ba6192, __VMLINUX_SYMBOL_STR(scsi_is_host_device) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x9d0875c8, __VMLINUX_SYMBOL_STR(crypto_alloc_ahash) },
	{ 0x5018fc35, __VMLINUX_SYMBOL_STR(iscsi_tcp_conn_setup) },
	{ 0x5256634b, __VMLINUX_SYMBOL_STR(iscsi_tcp_recv_skb) },
	{ 0x6f656240, __VMLINUX_SYMBOL_STR(tcp_read_sock) },
	{ 0x56ef57ae, __VMLINUX_SYMBOL_STR(iscsi_conn_queue_work) },
	{ 0x291ce332, __VMLINUX_SYMBOL_STR(iscsi_tcp_hdr_recv_prep) },
	{ 0xb33ccf56, __VMLINUX_SYMBOL_STR(sk_set_memalloc) },
	{ 0xf6a8f78e, __VMLINUX_SYMBOL_STR(iscsi_conn_bind) },
	{ 0xed874ab8, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0x78725b3, __VMLINUX_SYMBOL_STR(iscsi_conn_stop) },
	{ 0xd2259743, __VMLINUX_SYMBOL_STR(iscsi_suspend_tx) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xdd12e932, __VMLINUX_SYMBOL_STR(iscsi_tcp_conn_teardown) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x7a4497db, __VMLINUX_SYMBOL_STR(kzfree) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x3a6c7f80, __VMLINUX_SYMBOL_STR(iscsi_tcp_set_max_r2t) },
	{ 0x91d2e494, __VMLINUX_SYMBOL_STR(iscsi_set_param) },
	{ 0x76562304, __VMLINUX_SYMBOL_STR(kernel_getpeername) },
	{ 0xcfc967d8, __VMLINUX_SYMBOL_STR(iscsi_conn_get_param) },
	{ 0x6ba3eaf, __VMLINUX_SYMBOL_STR(iscsi_host_get_param) },
	{ 0xbf8c9136, __VMLINUX_SYMBOL_STR(iscsi_conn_get_addr_param) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x32432d08, __VMLINUX_SYMBOL_STR(kernel_getsockname) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x762a1b81, __VMLINUX_SYMBOL_STR(iscsi_tcp_conn_get_stats) },
	{ 0x4a60a854, __VMLINUX_SYMBOL_STR(iscsi_tcp_segment_unmap) },
	{ 0x6a9eaef1, __VMLINUX_SYMBOL_STR(iscsi_tcp_segment_done) },
	{ 0x7c0a1fb, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x45b9cf27, __VMLINUX_SYMBOL_STR(iscsi_conn_failure) },
	{ 0x4c233a44, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x4c5fc58c, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9e31ab80, __VMLINUX_SYMBOL_STR(iscsi_segment_seek_sg) },
	{ 0xdcf196a1, __VMLINUX_SYMBOL_STR(iscsi_segment_init_linear) },
	{ 0x47ab89b9, __VMLINUX_SYMBOL_STR(iscsi_tcp_dgst_header) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xdb290d52, __VMLINUX_SYMBOL_STR(dev_printk) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libiscsi,libiscsi_tcp";


MODULE_INFO(srcversion, "998BB0E00562E4AA755118E");
