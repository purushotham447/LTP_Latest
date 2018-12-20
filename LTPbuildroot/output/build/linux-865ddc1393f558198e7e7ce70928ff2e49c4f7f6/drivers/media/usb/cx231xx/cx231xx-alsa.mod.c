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
	{ 0xfb42e82, __VMLINUX_SYMBOL_STR(is_fw_load) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbe6d3e2e, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0x653e8626, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x74b8e92e, __VMLINUX_SYMBOL_STR(snd_pcm_stream_lock) },
	{ 0xfaa1ad97, __VMLINUX_SYMBOL_STR(usb_unlink_urb) },
	{ 0xe95180fd, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_integer) },
	{ 0x1fbf636a, __VMLINUX_SYMBOL_STR(cx231xx_register_extension) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x16b19dbb, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xc009e8c2, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0xde7f6d09, __VMLINUX_SYMBOL_STR(snd_card_new) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x43497351, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xd7765585, __VMLINUX_SYMBOL_STR(snd_pcm_stream_unlock) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x935dae6a, __VMLINUX_SYMBOL_STR(cx231xx_capture_start) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xcc7685a3, __VMLINUX_SYMBOL_STR(cx231xx_set_alt_setting) },
	{ 0x72f4eb3d, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0x97faf372, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xccf3e878, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x1399c287, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x6ebc1f5f, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xd07745e6, __VMLINUX_SYMBOL_STR(cx231xx_unregister_extension) },
	{ 0x54b8b402, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cx231xx,snd-pcm,snd";


MODULE_INFO(srcversion, "747F55FF7A38E0309D698D6");
