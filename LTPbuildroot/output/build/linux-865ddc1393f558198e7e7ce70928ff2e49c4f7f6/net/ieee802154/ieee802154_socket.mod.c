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
	{ 0xc1ba9023, __VMLINUX_SYMBOL_STR(dev_load) },
	{ 0xa357ee7c, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xea2b1e9b, __VMLINUX_SYMBOL_STR(dev_getbyhwaddr_rcu) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x96f9556, __VMLINUX_SYMBOL_STR(dev_get_by_name) },
	{ 0x50b1df54, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0xb2a44214, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x8d1abaa6, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x9d84537f, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x56861aec, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0x88761f21, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x1c2e9509, __VMLINUX_SYMBOL_STR(sock_get_timestamp) },
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xd7c09a05, __VMLINUX_SYMBOL_STR(ieee802154_hdr_pull) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xe30ca76e, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x9799bd67, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iter) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x32b890e3, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x81c088a0, __VMLINUX_SYMBOL_STR(sock_prot_inuse_add) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x34c24a5f, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0x8ca64545, __VMLINUX_SYMBOL_STR(dev_remove_pack) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0xc5d3cb8e, __VMLINUX_SYMBOL_STR(__sock_recv_ts_and_drops) },
	{ 0xa30966fc, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x3092049e, __VMLINUX_SYMBOL_STR(sock_get_timestampns) },
	{ 0x68792659, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0xf39996f5, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0xcf9a5d95, __VMLINUX_SYMBOL_STR(dev_getfirstbyhwtype) },
	{ 0x48da9d64, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf6f8bc64, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x245f6747, __VMLINUX_SYMBOL_STR(_copy_from_iter_full) },
	{ 0x6b21443b, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x5d66220b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xc0056be5, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0x2c0e20d2, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x6ec9ccdb, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xcd12d02f, __VMLINUX_SYMBOL_STR(dev_add_pack) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x81f8afb7, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x7529a1e4, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xece08088, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ieee802154";


MODULE_INFO(srcversion, "59C0C3FFC08E1B73CF5837F");
