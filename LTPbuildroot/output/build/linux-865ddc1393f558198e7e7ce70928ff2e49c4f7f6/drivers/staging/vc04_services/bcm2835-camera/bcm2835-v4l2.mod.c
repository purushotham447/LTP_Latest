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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa32d90fb, __VMLINUX_SYMBOL_STR(vb2_ioctl_reqbufs) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa6327171, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x6b3c2e66, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x612cd918, __VMLINUX_SYMBOL_STR(v4l2_ctrl_log_status) },
	{ 0x686df339, __VMLINUX_SYMBOL_STR(vchi_initialise) },
	{ 0xf227e770, __VMLINUX_SYMBOL_STR(vchi_service_open) },
	{ 0x8e079795, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0xb9218b73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xf3f55b0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xd7ef7b1f, __VMLINUX_SYMBOL_STR(vb2_fop_poll) },
	{ 0x43e7e7b5, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamon) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x45a172d0, __VMLINUX_SYMBOL_STR(vchi_queue_kernel_message) },
	{ 0xa24295ba, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd70639cc, __VMLINUX_SYMBOL_STR(btree_destroy) },
	{ 0x974501cf, __VMLINUX_SYMBOL_STR(vchi_msg_hold) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x73be3770, __VMLINUX_SYMBOL_STR(vchi_service_use) },
	{ 0x587c8df5, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xd2a00c9d, __VMLINUX_SYMBOL_STR(vb2_fop_read) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x684037a, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xadc8f144, __VMLINUX_SYMBOL_STR(vb2_vmalloc_memops) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xccbc86d2, __VMLINUX_SYMBOL_STR(vb2_fop_mmap) },
	{ 0x95d7425d, __VMLINUX_SYMBOL_STR(vb2_ioctl_qbuf) },
	{ 0x6c49fc55, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x44e4c065, __VMLINUX_SYMBOL_STR(vchi_held_msg_release) },
	{ 0x3b321ff8, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xcf64918b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x8f74a575, __VMLINUX_SYMBOL_STR(vb2_plane_vaddr) },
	{ 0xd83ff860, __VMLINUX_SYMBOL_STR(vb2_buffer_done) },
	{ 0x3ca7dbcc, __VMLINUX_SYMBOL_STR(vchi_connect) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xf5195826, __VMLINUX_SYMBOL_STR(vb2_ioctl_prepare_buf) },
	{ 0xa674f029, __VMLINUX_SYMBOL_STR(vb2_ioctl_create_bufs) },
	{ 0xd836e11d, __VMLINUX_SYMBOL_STR(vb2_ioctl_dqbuf) },
	{ 0x48244456, __VMLINUX_SYMBOL_STR(vchi_service_close) },
	{ 0x583ffdeb, __VMLINUX_SYMBOL_STR(btree_init) },
	{ 0x615e5eb0, __VMLINUX_SYMBOL_STR(btree_lookup) },
	{ 0x77e60d1e, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_int_menu) },
	{ 0xf5ef842e, __VMLINUX_SYMBOL_STR(v4l_bound_align_image) },
	{ 0x76aa53c2, __VMLINUX_SYMBOL_STR(vb2_fop_release) },
	{ 0x9f914a5a, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xf331236f, __VMLINUX_SYMBOL_STR(btree_geo32) },
	{ 0x507f24a9, __VMLINUX_SYMBOL_STR(v4l2_ctrl_auto_cluster) },
	{ 0x2394bc74, __VMLINUX_SYMBOL_STR(vchi_service_release) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x4c1d561b, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0x48a71812, __VMLINUX_SYMBOL_STR(btree_remove) },
	{ 0xd1ae811f, __VMLINUX_SYMBOL_STR(vb2_ioctl_querybuf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9c74279b, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xdbd38f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x689e06e, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xf68fb683, __VMLINUX_SYMBOL_STR(btree_insert) },
	{ 0x8dc96cb8, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamoff) },
	{ 0x4e9a9f81, __VMLINUX_SYMBOL_STR(vchi_bulk_queue_receive) },
	{ 0x29dec96f, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0x8e20e351, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x7be88e08, __VMLINUX_SYMBOL_STR(vb2_queue_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-v4l2,videodev,videobuf2-vmalloc,videobuf2-core,v4l2-common";


MODULE_INFO(srcversion, "537B6432CDA89C2956E9B97");
