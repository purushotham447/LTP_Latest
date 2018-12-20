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
	{ 0x1c1b549c, __VMLINUX_SYMBOL_STR(class_find_device) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x60d060e4, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xac9657d8, __VMLINUX_SYMBOL_STR(ktime_get_with_offset) },
	{ 0x7d45df8, __VMLINUX_SYMBOL_STR(genl_register_family) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xe492077d, __VMLINUX_SYMBOL_STR(genl_unregister_family) },
	{ 0x9d158f29, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0xfa599bb2, __VMLINUX_SYMBOL_STR(netlink_register_notifier) },
	{ 0xfe90c4a6, __VMLINUX_SYMBOL_STR(_find_first_zero_bit_le) },
	{ 0xbb6d7fc8, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0x50f9c2e2, __VMLINUX_SYMBOL_STR(sock_no_ioctl) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xa37c95fa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x50b1df54, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xdf54a8f7, __VMLINUX_SYMBOL_STR(netlink_unregister_notifier) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x76099a0d, __VMLINUX_SYMBOL_STR(ida_simple_get) },
	{ 0x4cabed9, __VMLINUX_SYMBOL_STR(rfkill_register) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x9c9518d7, __VMLINUX_SYMBOL_STR(skb_unlink) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xaad8c7d6, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x4d7e95cb, __VMLINUX_SYMBOL_STR(__sock_recv_wifi_status) },
	{ 0xdd9891e1, __VMLINUX_SYMBOL_STR(device_del) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x10db8992, __VMLINUX_SYMBOL_STR(class_dev_iter_init) },
	{ 0x6b60071a, __VMLINUX_SYMBOL_STR(rfkill_alloc) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xdc781e3b, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xdfc0c78e, __VMLINUX_SYMBOL_STR(ida_simple_remove) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xd100acbd, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x4124ced2, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x2f670f3d, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x1e445ab7, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0x7ec5844a, __VMLINUX_SYMBOL_STR(devm_kfree) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0xa889a3af, __VMLINUX_SYMBOL_STR(__sock_recv_timestamp) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xe7cd355, __VMLINUX_SYMBOL_STR(netlink_broadcast) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0xf39996f5, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0xcdbca9b6, __VMLINUX_SYMBOL_STR(class_dev_iter_exit) },
	{ 0x5d649bdf, __VMLINUX_SYMBOL_STR(genl_family_attrbuf) },
	{ 0x6b21443b, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0x254c6bdc, __VMLINUX_SYMBOL_STR(__pskb_copy_fclone) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xfb55dff3, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xdb68bbad, __VMLINUX_SYMBOL_STR(rfkill_destroy) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xedd7e40b, __VMLINUX_SYMBOL_STR(genlmsg_put) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0x1f1ac42d, __VMLINUX_SYMBOL_STR(sock_no_sendmsg) },
	{ 0x6cdc5c6b, __VMLINUX_SYMBOL_STR(nla_strlcpy) },
	{ 0x23fa0429, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0x64a068b1, __VMLINUX_SYMBOL_STR(add_wait_queue_exclusive) },
	{ 0xc0763484, __VMLINUX_SYMBOL_STR(rfkill_blocked) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x4a395dbd, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x83eb21c, __VMLINUX_SYMBOL_STR(rfkill_unregister) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xcea2a4ef, __VMLINUX_SYMBOL_STR(class_dev_iter_next) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rfkill";


MODULE_INFO(srcversion, "7441920A6E7B30323CBE8AC");
