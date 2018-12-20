#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
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
	{ 0xd7e0995a, __VMLINUX_SYMBOL_STR(vb2_core_streamoff) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe9166385, __VMLINUX_SYMBOL_STR(vb2_core_dqbuf) },
	{ 0xcf35ab7, __VMLINUX_SYMBOL_STR(vb2_mmap) },
	{ 0xa95520b3, __VMLINUX_SYMBOL_STR(vb2_core_qbuf) },
	{ 0xc48aa878, __VMLINUX_SYMBOL_STR(vb2_core_querybuf) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xb529104, __VMLINUX_SYMBOL_STR(vb2_core_streamon) },
	{ 0x35afa495, __VMLINUX_SYMBOL_STR(vb2_core_poll) },
	{ 0x4ed19e9a, __VMLINUX_SYMBOL_STR(vb2_read) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x68a6e8a2, __VMLINUX_SYMBOL_STR(vb2_core_prepare_buf) },
	{ 0x6c49fc55, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf94f8a16, __VMLINUX_SYMBOL_STR(v4l2_event_pending) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x7b8ace28, __VMLINUX_SYMBOL_STR(v4l2_fh_release) },
	{ 0x5d123284, __VMLINUX_SYMBOL_STR(vb2_core_queue_release) },
	{ 0x348247a7, __VMLINUX_SYMBOL_STR(vb2_write) },
	{ 0x9f914a5a, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xe22df8d0, __VMLINUX_SYMBOL_STR(vb2_core_create_bufs) },
	{ 0x9e86514d, __VMLINUX_SYMBOL_STR(vb2_core_expbuf) },
	{ 0xa7de5fdd, __VMLINUX_SYMBOL_STR(vb2_core_reqbufs) },
	{ 0x85649680, __VMLINUX_SYMBOL_STR(vb2_verify_memory_type) },
	{ 0x3344e1b5, __VMLINUX_SYMBOL_STR(vb2_core_queue_init) },
	{ 0x7e2fdf2, __VMLINUX_SYMBOL_STR(vb2_buffer_in_use) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-core,videodev";


MODULE_INFO(srcversion, "0F530711EC55E2D36AE37A6");
