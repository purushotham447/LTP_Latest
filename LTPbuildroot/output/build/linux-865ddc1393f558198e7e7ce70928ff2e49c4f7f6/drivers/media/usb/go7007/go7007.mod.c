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
	{ 0xa32d90fb, __VMLINUX_SYMBOL_STR(vb2_ioctl_reqbufs) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa6327171, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x6b3c2e66, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb3d2facd, __VMLINUX_SYMBOL_STR(v4l2_event_queue) },
	{ 0x612cd918, __VMLINUX_SYMBOL_STR(v4l2_ctrl_log_status) },
	{ 0xbe6d3e2e, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0x8e079795, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0xb9218b73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x6cec570d, __VMLINUX_SYMBOL_STR(v4l2_ctrl_g_ctrl) },
	{ 0xf3f55b0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xd7ef7b1f, __VMLINUX_SYMBOL_STR(vb2_fop_poll) },
	{ 0x43e7e7b5, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamon) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xebcc823a, __VMLINUX_SYMBOL_STR(vb2_ops_wait_prepare) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xa24295ba, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x7569743c, __VMLINUX_SYMBOL_STR(snd_card_disconnect) },
	{ 0x53f6de4e, __VMLINUX_SYMBOL_STR(i2c_add_adapter) },
	{ 0x587c8df5, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xd2a00c9d, __VMLINUX_SYMBOL_STR(vb2_fop_read) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x684037a, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xe18754ca, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xadc8f144, __VMLINUX_SYMBOL_STR(vb2_vmalloc_memops) },
	{ 0x8df22a32, __VMLINUX_SYMBOL_STR(snd_device_new) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xccbc86d2, __VMLINUX_SYMBOL_STR(vb2_fop_mmap) },
	{ 0x95d7425d, __VMLINUX_SYMBOL_STR(vb2_ioctl_qbuf) },
	{ 0xd5ccab41, __VMLINUX_SYMBOL_STR(v4l2_event_subscribe) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x16b19dbb, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0xcf64918b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x8f74a575, __VMLINUX_SYMBOL_STR(vb2_plane_vaddr) },
	{ 0xd83ff860, __VMLINUX_SYMBOL_STR(vb2_buffer_done) },
	{ 0x69dddddf, __VMLINUX_SYMBOL_STR(snd_card_free_when_closed) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x5e663669, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_custom) },
	{ 0xc009e8c2, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0xd836e11d, __VMLINUX_SYMBOL_STR(vb2_ioctl_dqbuf) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0xde7f6d09, __VMLINUX_SYMBOL_STR(snd_card_new) },
	{ 0x2d28e0e8, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x76aa53c2, __VMLINUX_SYMBOL_STR(vb2_fop_release) },
	{ 0x9f914a5a, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x6334519b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_grab) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x4c1d561b, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xd1ae811f, __VMLINUX_SYMBOL_STR(vb2_ioctl_querybuf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9c74279b, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xdbd38f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x8b324df5, __VMLINUX_SYMBOL_STR(vb2_ops_wait_finish) },
	{ 0x9f6efab6, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x72f4eb3d, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0x9e2b4838, __VMLINUX_SYMBOL_STR(v4l2_i2c_new_subdev_board) },
	{ 0x97faf372, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xccf3e878, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x1399c287, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x8dc96cb8, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamoff) },
	{ 0xd7db2c8b, __VMLINUX_SYMBOL_STR(v4l2_device_put) },
	{ 0x2ebcd9e7, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x8e20e351, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x7be88e08, __VMLINUX_SYMBOL_STR(vb2_queue_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-v4l2,videodev,snd-pcm,snd,videobuf2-vmalloc,videobuf2-core,v4l2-common";


MODULE_INFO(srcversion, "4C66E5CE3480A48B1F181BB");
