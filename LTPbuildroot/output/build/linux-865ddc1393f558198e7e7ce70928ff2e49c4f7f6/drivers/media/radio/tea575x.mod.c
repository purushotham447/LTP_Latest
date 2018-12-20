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
	{ 0xa6327171, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x6b3c2e66, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x612cd918, __VMLINUX_SYMBOL_STR(v4l2_ctrl_log_status) },
	{ 0xb9218b73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xf3f55b0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xa24295ba, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3b321ff8, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xcf64918b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x7b8ace28, __VMLINUX_SYMBOL_STR(v4l2_fh_release) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x9f914a5a, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xfd89531, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_setup) },
	{ 0x4c1d561b, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0x54496b4, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0xdbd38f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x8e20e351, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x395d0ed0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_poll) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videodev";


MODULE_INFO(srcversion, "BA23D78DB7932274F1C16C5");
