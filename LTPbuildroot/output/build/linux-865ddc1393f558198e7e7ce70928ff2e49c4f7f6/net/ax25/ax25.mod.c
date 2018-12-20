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
	{ 0xc0fec0d4, __VMLINUX_SYMBOL_STR(proc_dointvec_minmax) },
	{ 0x60d060e4, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x497d23ba, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0x2068e934, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xad73041f, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xcdfe35a3, __VMLINUX_SYMBOL_STR(unregister_net_sysctl_table) },
	{ 0x1391f507, __VMLINUX_SYMBOL_STR(send_sig) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x96f9556, __VMLINUX_SYMBOL_STR(dev_get_by_name) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xa37c95fa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x75bda77a, __VMLINUX_SYMBOL_STR(seq_hlist_next) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x50579830, __VMLINUX_SYMBOL_STR(skb_set_owner_w) },
	{ 0x622684f4, __VMLINUX_SYMBOL_STR(sock_i_ino) },
	{ 0xd914333e, __VMLINUX_SYMBOL_STR(sock_rfree) },
	{ 0x2f390b4c, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x3e72ef7b, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x1c2e9509, __VMLINUX_SYMBOL_STR(sock_get_timestamp) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xe60f0743, __VMLINUX_SYMBOL_STR(skb_dequeue_tail) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x3dfc897c, __VMLINUX_SYMBOL_STR(seq_hlist_start_head) },
	{ 0x543ef284, __VMLINUX_SYMBOL_STR(seq_hlist_start) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd100acbd, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x8ca64545, __VMLINUX_SYMBOL_STR(dev_remove_pack) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x62451f4, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x3092049e, __VMLINUX_SYMBOL_STR(sock_get_timestampns) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0xf39996f5, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0x6b21443b, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x4c5fc58c, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x4c233a44, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6f5696fb, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x4a395dbd, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xcd12d02f, __VMLINUX_SYMBOL_STR(dev_add_pack) },
	{ 0x8296f8de, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x2a628db, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x81f8afb7, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x4dc66bb, __VMLINUX_SYMBOL_STR(register_net_sysctl) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FEC4DD474221345BBE60245");
