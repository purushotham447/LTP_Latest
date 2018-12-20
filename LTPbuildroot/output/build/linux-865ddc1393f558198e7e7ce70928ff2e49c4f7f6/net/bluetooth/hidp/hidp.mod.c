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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x60d060e4, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x1b3adb90, __VMLINUX_SYMBOL_STR(hid_add_device) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xab18a277, __VMLINUX_SYMBOL_STR(hid_ignore) },
	{ 0xe439a287, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x7c0a1fb, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0xed874ab8, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x9d158f29, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0xd0b85750, __VMLINUX_SYMBOL_STR(hid_parse_report) },
	{ 0xbb6d7fc8, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xb308c97d, __VMLINUX_SYMBOL_STR(wait_woken) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x50b1df54, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x83dc8866, __VMLINUX_SYMBOL_STR(bt_sock_register) },
	{ 0x27168320, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x98c250de, __VMLINUX_SYMBOL_STR(sock_no_poll) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xd6fcc05f, __VMLINUX_SYMBOL_STR(hid_input_report) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x67d487a2, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x47022514, __VMLINUX_SYMBOL_STR(bt_err) },
	{ 0xd7442057, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xff3e3628, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xab7380c9, __VMLINUX_SYMBOL_STR(sock_no_recvmsg) },
	{ 0xacfddd, __VMLINUX_SYMBOL_STR(bt_sock_unlink) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xed98fa6c, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xae25c4f0, __VMLINUX_SYMBOL_STR(l2cap_conn_put) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x6c49fc55, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xe22348a5, __VMLINUX_SYMBOL_STR(l2cap_is_socket) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x8fea24bd, __VMLINUX_SYMBOL_STR(bt_sock_unregister) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x3e3ec986, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x75b9f0e4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x72287035, __VMLINUX_SYMBOL_STR(bt_sock_link) },
	{ 0x9ba94644, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xd0654aba, __VMLINUX_SYMBOL_STR(woken_wake_function) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x67db99b8, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0xc24a1ee1, __VMLINUX_SYMBOL_STR(l2cap_register_user) },
	{ 0x550b7b2e, __VMLINUX_SYMBOL_STR(__module_put_and_exit) },
	{ 0xf4bfa21, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xadb3e6ca, __VMLINUX_SYMBOL_STR(hid_destroy_device) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x6bdb1dd3, __VMLINUX_SYMBOL_STR(hid_allocate_device) },
	{ 0x54a33e60, __VMLINUX_SYMBOL_STR(l2cap_conn_get) },
	{ 0x577bbc5d, __VMLINUX_SYMBOL_STR(get_device) },
	{ 0x2492d879, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xfb55dff3, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x38dad6e5, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x1f1ac42d, __VMLINUX_SYMBOL_STR(sock_no_sendmsg) },
	{ 0x4a69ceea, __VMLINUX_SYMBOL_STR(set_user_nice) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x8c3adebf, __VMLINUX_SYMBOL_STR(bt_procfs_init) },
	{ 0x4a395dbd, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xe2e8065e, __VMLINUX_SYMBOL_STR(memdup_user) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xfea5e085, __VMLINUX_SYMBOL_STR(bt_procfs_cleanup) },
	{ 0x4dec6038, __VMLINUX_SYMBOL_STR(memscan) },
	{ 0xe6986ac3, __VMLINUX_SYMBOL_STR(l2cap_unregister_user) },
	{ 0xf811ecfb, __VMLINUX_SYMBOL_STR(input_allocate_device) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=bluetooth";


MODULE_INFO(srcversion, "C9183395855790F1C5A8149");
