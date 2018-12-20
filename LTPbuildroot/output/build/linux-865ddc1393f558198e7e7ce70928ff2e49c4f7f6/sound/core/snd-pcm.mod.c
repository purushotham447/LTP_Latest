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
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x24a94b26, __VMLINUX_SYMBOL_STR(snd_info_get_line) },
	{ 0x8e06dfa1, __VMLINUX_SYMBOL_STR(put_pid) },
	{ 0x2ee0613d, __VMLINUX_SYMBOL_STR(dma_release_from_dev_coherent) },
	{ 0xe439a287, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xd71f8fab, __VMLINUX_SYMBOL_STR(snd_register_device) },
	{ 0x7d77eaae, __VMLINUX_SYMBOL_STR(snd_device_register) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xea124bd1, __VMLINUX_SYMBOL_STR(gcd) },
	{ 0xc1d8cfaf, __VMLINUX_SYMBOL_STR(__fdget) },
	{ 0x84ba5e50, __VMLINUX_SYMBOL_STR(snd_card_file_remove) },
	{ 0xaaf68885, __VMLINUX_SYMBOL_STR(snd_device_free) },
	{ 0x43c91d37, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0x1cf28d74, __VMLINUX_SYMBOL_STR(pid_vnr) },
	{ 0xb5a57d8a, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xc56d9535, __VMLINUX_SYMBOL_STR(snd_power_wait) },
	{ 0xfabd746e, __VMLINUX_SYMBOL_STR(snd_device_initialize) },
	{ 0xd9eb8ddc, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xe68dcd21, __VMLINUX_SYMBOL_STR(snd_info_create_card_entry) },
	{ 0xf3cd0d92, __VMLINUX_SYMBOL_STR(pm_qos_add_request) },
	{ 0xb8972014, __VMLINUX_SYMBOL_STR(pm_qos_remove_request) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xb2e5ae4a, __VMLINUX_SYMBOL_STR(snd_lookup_minor_data) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x5f07b6e9, __VMLINUX_SYMBOL_STR(of_gen_pool_get) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xf4c91ed, __VMLINUX_SYMBOL_STR(ns_to_timespec) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0xd1ae5f77, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x7f23a6b3, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x67d487a2, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x348dd463, __VMLINUX_SYMBOL_STR(down_write_trylock) },
	{ 0x3d92850a, __VMLINUX_SYMBOL_STR(dma_alloc_from_dev_coherent) },
	{ 0x64814226, __VMLINUX_SYMBOL_STR(snd_ctl_unregister_ioctl) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xaad8c7d6, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8df22a32, __VMLINUX_SYMBOL_STR(snd_device_new) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x97606ce3, __VMLINUX_SYMBOL_STR(snd_timer_new) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x18bd76a4, __VMLINUX_SYMBOL_STR(_raw_spin_trylock) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xf922c6f3, __VMLINUX_SYMBOL_STR(snd_unregister_device) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x9beb535e, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8f595b11, __VMLINUX_SYMBOL_STR(snd_major) },
	{ 0x3e3ec986, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x52cb8a18, __VMLINUX_SYMBOL_STR(snd_card_file_add) },
	{ 0x6380fec7, __VMLINUX_SYMBOL_STR(snd_ctl_register_ioctl) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x8ddd8aad, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x880cb6a3, __VMLINUX_SYMBOL_STR(pm_qos_request_active) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xed7fe89b, __VMLINUX_SYMBOL_STR(snd_ctl_new1) },
	{ 0x11dc0fdf, __VMLINUX_SYMBOL_STR(gen_pool_dma_alloc) },
	{ 0x94eea794, __VMLINUX_SYMBOL_STR(getnstimeofday64) },
	{ 0xb5c00014, __VMLINUX_SYMBOL_STR(_raw_write_lock_irq) },
	{ 0x31380354, __VMLINUX_SYMBOL_STR(getrawmonotonic64) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x3f892be0, __VMLINUX_SYMBOL_STR(snd_ctl_remove) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xdd31568b, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x9e6d79f8, __VMLINUX_SYMBOL_STR(snd_info_get_str) },
	{ 0x28d6861d, __VMLINUX_SYMBOL_STR(__vmalloc) },
	{ 0x54496b4, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xe22b690d, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xad83198b, __VMLINUX_SYMBOL_STR(snd_info_free_entry) },
	{ 0xa6813a7d, __VMLINUX_SYMBOL_STR(snd_timer_interrupt) },
	{ 0x6128b5fc, __VMLINUX_SYMBOL_STR(__printk_ratelimit) },
	{ 0x1db7dc40, __VMLINUX_SYMBOL_STR(pgprot_kernel) },
	{ 0xb9fa3b47, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0xbdbfdb20, __VMLINUX_SYMBOL_STR(dma_common_mmap) },
	{ 0x3eb582fb, __VMLINUX_SYMBOL_STR(snd_ctl_get_preferred_subdevice) },
	{ 0x1867a8f9, __VMLINUX_SYMBOL_STR(snd_timer_notify) },
	{ 0xe2e8065e, __VMLINUX_SYMBOL_STR(memdup_user) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x1399c287, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x8e49e81b, __VMLINUX_SYMBOL_STR(snd_ctl_add) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x5e515be6, __VMLINUX_SYMBOL_STR(ktime_get_ts64) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x68640290, __VMLINUX_SYMBOL_STR(gen_pool_free) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0xcfd61927, __VMLINUX_SYMBOL_STR(snd_info_create_module_entry) },
	{ 0x676785b3, __VMLINUX_SYMBOL_STR(snd_info_register) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd,snd-timer";


MODULE_INFO(srcversion, "3DBA4FD7CCF2C70930404DB");
