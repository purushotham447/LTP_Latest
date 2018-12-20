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
	{ 0xe37ae932, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xbb6d7fc8, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0x9d158f29, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x50f9c2e2, __VMLINUX_SYMBOL_STR(sock_no_ioctl) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x50b1df54, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xfb55dff3, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x796d600f, __VMLINUX_SYMBOL_STR(xfrm_register_km) },
	{ 0xf39996f5, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0xbe118033, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x8302795c, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0x44b60584, __VMLINUX_SYMBOL_STR(xfrm_unregister_km) },
	{ 0x7a8ca627, __VMLINUX_SYMBOL_STR(xfrm_count_pfkey_enc_supported) },
	{ 0xa575945, __VMLINUX_SYMBOL_STR(xfrm_count_pfkey_auth_supported) },
	{ 0x28e23139, __VMLINUX_SYMBOL_STR(xfrm_probe_algs) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x70d982fd, __VMLINUX_SYMBOL_STR(xfrm_alloc_spi) },
	{ 0xf10526ac, __VMLINUX_SYMBOL_STR(verify_spi_info) },
	{ 0x34ca2faf, __VMLINUX_SYMBOL_STR(xfrm_find_acq) },
	{ 0x47b34e60, __VMLINUX_SYMBOL_STR(xfrm_ealg_get_byname) },
	{ 0x3bf471d7, __VMLINUX_SYMBOL_STR(xfrm_calg_get_byname) },
	{ 0xa6e66685, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byname) },
	{ 0xdbfc35c8, __VMLINUX_SYMBOL_STR(xfrm_ealg_get_byidx) },
	{ 0xaa762fe2, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byidx) },
	{ 0xb2ee2d63, __VMLINUX_SYMBOL_STR(xfrm_policy_byid) },
	{ 0xad1b60ed, __VMLINUX_SYMBOL_STR(xfrm_calg_get_byid) },
	{ 0x834ba96d, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byid) },
	{ 0x6fbd0899, __VMLINUX_SYMBOL_STR(xfrm_state_add) },
	{ 0x4a4106d, __VMLINUX_SYMBOL_STR(xfrm_state_update) },
	{ 0xc7f0a0c0, __VMLINUX_SYMBOL_STR(xfrm_init_state) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xdfea3a6d, __VMLINUX_SYMBOL_STR(xfrm_ealg_get_byid) },
	{ 0x87b5d9d9, __VMLINUX_SYMBOL_STR(xfrm_state_alloc) },
	{ 0xa69b96cd, __VMLINUX_SYMBOL_STR(xfrm_state_delete) },
	{ 0xb19762e0, __VMLINUX_SYMBOL_STR(xfrm_policy_insert) },
	{ 0x6b555b38, __VMLINUX_SYMBOL_STR(xfrm_policy_bysel_ctx) },
	{ 0x1e9edfb7, __VMLINUX_SYMBOL_STR(seq_hlist_start_head_rcu) },
	{ 0x67b78eb3, __VMLINUX_SYMBOL_STR(seq_hlist_next_rcu) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x622684f4, __VMLINUX_SYMBOL_STR(sock_i_ino) },
	{ 0x497d23ba, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0xe163a4f3, __VMLINUX_SYMBOL_STR(sock_i_uid) },
	{ 0xa86cdd09, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0x2a628db, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x9f82eb6e, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
	{ 0xa23400b1, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xdf109ce8, __VMLINUX_SYMBOL_STR(xfrm_find_acq_byseq) },
	{ 0x702990ad, __VMLINUX_SYMBOL_STR(km_state_notify) },
	{ 0x2251dae7, __VMLINUX_SYMBOL_STR(xfrm_state_flush) },
	{ 0x73c43fd0, __VMLINUX_SYMBOL_STR(xfrm_state_walk) },
	{ 0xb31fa32b, __VMLINUX_SYMBOL_STR(xfrm_state_walk_done) },
	{ 0x83b009ea, __VMLINUX_SYMBOL_STR(xfrm_state_walk_init) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa37c95fa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0x74a6adb7, __VMLINUX_SYMBOL_STR(km_policy_notify) },
	{ 0x940d799f, __VMLINUX_SYMBOL_STR(xfrm_policy_flush) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x32b890e3, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0xc5d3cb8e, __VMLINUX_SYMBOL_STR(__sock_recv_ts_and_drops) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe4b6857c, __VMLINUX_SYMBOL_STR(xfrm_policy_destroy) },
	{ 0x1e64a1ed, __VMLINUX_SYMBOL_STR(xfrm_policy_alloc) },
	{ 0xf29a509e, __VMLINUX_SYMBOL_STR(xfrm_policy_walk_done) },
	{ 0xe5ed5467, __VMLINUX_SYMBOL_STR(xfrm_policy_walk_init) },
	{ 0x1993438c, __VMLINUX_SYMBOL_STR(xfrm_policy_walk) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xd914333e, __VMLINUX_SYMBOL_STR(sock_rfree) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E5606185C53B99A1CA84181");
