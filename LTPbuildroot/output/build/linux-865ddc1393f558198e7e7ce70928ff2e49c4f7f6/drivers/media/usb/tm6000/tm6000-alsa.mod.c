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
	{ 0x9c74279b, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xc009e8c2, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0x81f48296, __VMLINUX_SYMBOL_STR(tm6000_unregister_extension) },
	{ 0x440864e1, __VMLINUX_SYMBOL_STR(tm6000_register_extension) },
	{ 0x97faf372, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0x16b19dbb, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0xccf3e878, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc31d6d33, __VMLINUX_SYMBOL_STR(snd_component_add) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xde7f6d09, __VMLINUX_SYMBOL_STR(snd_card_new) },
	{ 0xe95180fd, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_integer) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x6271af43, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_pow2) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1399c287, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x2adecea7, __VMLINUX_SYMBOL_STR(tm6000_set_audio_bitrate) },
	{ 0x1500594b, __VMLINUX_SYMBOL_STR(tm6000_set_reg_mask) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x72f4eb3d, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0xbe6d3e2e, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0xd7765585, __VMLINUX_SYMBOL_STR(snd_pcm_stream_unlock) },
	{ 0x74b8e92e, __VMLINUX_SYMBOL_STR(snd_pcm_stream_lock) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-pcm,tm6000,snd";


MODULE_INFO(srcversion, "C81042C249EE84580C5DE0D");
