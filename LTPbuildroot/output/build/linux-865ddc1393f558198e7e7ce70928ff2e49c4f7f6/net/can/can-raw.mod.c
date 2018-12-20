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
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x71d9f1e9, __VMLINUX_SYMBOL_STR(can_rx_register) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe4823cf, __VMLINUX_SYMBOL_STR(can_proto_unregister) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x437a0d6d, __VMLINUX_SYMBOL_STR(__sock_tx_timestamp) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x34c24a5f, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0xf7084192, __VMLINUX_SYMBOL_STR(can_ioctl) },
	{ 0x68ff7389, __VMLINUX_SYMBOL_STR(can_send) },
	{ 0xc5d3cb8e, __VMLINUX_SYMBOL_STR(__sock_recv_ts_and_drops) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0xe8145c54, __VMLINUX_SYMBOL_STR(can_proto_register) },
	{ 0x6b21443b, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0xfb55dff3, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xe2e8065e, __VMLINUX_SYMBOL_STR(memdup_user) },
	{ 0xa2ea04a, __VMLINUX_SYMBOL_STR(can_rx_unregister) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xd840c793, __VMLINUX_SYMBOL_STR(_copy_to_iter) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can";


MODULE_INFO(srcversion, "FE29D0C167D2CC3E5A1F142");
