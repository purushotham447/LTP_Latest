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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc290cacb, __VMLINUX_SYMBOL_STR(usb_gstrings_attach) },
	{ 0x67ab9b5f, __VMLINUX_SYMBOL_STR(usb_free_all_descriptors) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x92215052, __VMLINUX_SYMBOL_STR(usb_ep_queue) },
	{ 0x18f3cfee, __VMLINUX_SYMBOL_STR(g_audio_cleanup) },
	{ 0x99460755, __VMLINUX_SYMBOL_STR(u_audio_start_capture) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb205404e, __VMLINUX_SYMBOL_STR(usb_function_unregister) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x9801f929, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x96e84f2b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb665c3e8, __VMLINUX_SYMBOL_STR(config_group_init_type_name) },
	{ 0x61666978, __VMLINUX_SYMBOL_STR(g_audio_setup) },
	{ 0x2a7d4194, __VMLINUX_SYMBOL_STR(usb_function_register) },
	{ 0x42c81dee, __VMLINUX_SYMBOL_STR(u_audio_stop_playback) },
	{ 0x7e92ee91, __VMLINUX_SYMBOL_STR(u_audio_stop_capture) },
	{ 0xde26cfae, __VMLINUX_SYMBOL_STR(u_audio_start_playback) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xbe2b40c, __VMLINUX_SYMBOL_STR(usb_assign_descriptors) },
	{ 0xaf347307, __VMLINUX_SYMBOL_STR(usb_interface_id) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,udc-core,u_audio";


MODULE_INFO(srcversion, "F190C38EB06964D90957F91");
