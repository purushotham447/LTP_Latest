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
	{ 0xcce4f200, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xbb6d7fc8, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0x9d158f29, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0xf01bf1ca, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x37d57af6, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x50f9c2e2, __VMLINUX_SYMBOL_STR(sock_no_ioctl) },
	{ 0xd5cb3a5d, __VMLINUX_SYMBOL_STR(af_alg_poll) },
	{ 0x50b1df54, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0x5df32c53, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xcb6c309b, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xfb55dff3, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0x17151793, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0xb90bc318, __VMLINUX_SYMBOL_STR(af_alg_release) },
	{ 0xa74a18d4, __VMLINUX_SYMBOL_STR(af_alg_unregister_type) },
	{ 0xeb032e2d, __VMLINUX_SYMBOL_STR(af_alg_register_type) },
	{ 0xfbd1b9d1, __VMLINUX_SYMBOL_STR(af_alg_wait_for_completion) },
	{ 0x25f69081, __VMLINUX_SYMBOL_STR(af_alg_wmem_wakeup) },
	{ 0x87c754b3, __VMLINUX_SYMBOL_STR(af_alg_get_rsgl) },
	{ 0x31de8f99, __VMLINUX_SYMBOL_STR(af_alg_alloc_areq) },
	{ 0xedef83aa, __VMLINUX_SYMBOL_STR(af_alg_wait_for_data) },
	{ 0x75360a9e, __VMLINUX_SYMBOL_STR(af_alg_free_resources) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0x12fdf3f8, __VMLINUX_SYMBOL_STR(af_alg_count_tsgl) },
	{ 0xd135496, __VMLINUX_SYMBOL_STR(af_alg_async_cb) },
	{ 0xec866aac, __VMLINUX_SYMBOL_STR(af_alg_complete) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6f3952e7, __VMLINUX_SYMBOL_STR(crypto_alloc_skcipher) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xd803b3ce, __VMLINUX_SYMBOL_STR(sock_kmalloc) },
	{ 0xa3c10d70, __VMLINUX_SYMBOL_STR(af_alg_release_parent) },
	{ 0x778231ea, __VMLINUX_SYMBOL_STR(sock_kfree_s) },
	{ 0xd63f72c1, __VMLINUX_SYMBOL_STR(sock_kzfree_s) },
	{ 0xaeb6b771, __VMLINUX_SYMBOL_STR(af_alg_pull_tsgl) },
	{ 0x572a8c16, __VMLINUX_SYMBOL_STR(af_alg_sendmsg) },
	{ 0x5bbba89c, __VMLINUX_SYMBOL_STR(af_alg_sendpage) },
	{ 0xb0e7f031, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x825eaf00, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x5ae749a0, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=af_alg";


MODULE_INFO(srcversion, "A36BA7DD70A725037CD8DCE");
