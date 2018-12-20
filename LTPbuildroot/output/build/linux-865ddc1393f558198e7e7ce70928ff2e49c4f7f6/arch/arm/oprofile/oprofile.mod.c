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
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xd20bf6ba, __VMLINUX_SYMBOL_STR(dcookie_unregister) },
	{ 0x75d87f97, __VMLINUX_SYMBOL_STR(__cpuhp_remove_state) },
	{ 0xe439a287, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xa9e18049, __VMLINUX_SYMBOL_STR(task_handoff_unregister) },
	{ 0xdd391eff, __VMLINUX_SYMBOL_STR(profile_event_unregister) },
	{ 0xc385cb58, __VMLINUX_SYMBOL_STR(perf_num_counters) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x2f4113a2, __VMLINUX_SYMBOL_STR(dcookie_register) },
	{ 0xf353a698, __VMLINUX_SYMBOL_STR(register_module_notifier) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x41fc8b39, __VMLINUX_SYMBOL_STR(perf_event_release_kernel) },
	{ 0xf5e34dcb, __VMLINUX_SYMBOL_STR(hrtimer_forward) },
	{ 0x6a5ecb18, __VMLINUX_SYMBOL_STR(unregister_module_notifier) },
	{ 0xeb19884d, __VMLINUX_SYMBOL_STR(ring_buffer_consume) },
	{ 0xe5785f57, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0xc65d3eed, __VMLINUX_SYMBOL_STR(ring_buffer_entries_cpu) },
	{ 0xd9eb8ddc, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xf156a974, __VMLINUX_SYMBOL_STR(free_task) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0xc95887f2, __VMLINUX_SYMBOL_STR(generic_delete_inode) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xd77f126b, __VMLINUX_SYMBOL_STR(dput) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x6d01cb72, __VMLINUX_SYMBOL_STR(ring_buffer_event_data) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xc06fe746, __VMLINUX_SYMBOL_STR(mount_single) },
	{ 0x1824c50, __VMLINUX_SYMBOL_STR(d_add) },
	{ 0x1f70e34, __VMLINUX_SYMBOL_STR(mmput) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xde573a9d, __VMLINUX_SYMBOL_STR(platform_device_register_full) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xd1ae5f77, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x67d487a2, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0xf4fc2d6c, __VMLINUX_SYMBOL_STR(__ring_buffer_alloc) },
	{ 0x46066e5b, __VMLINUX_SYMBOL_STR(perf_pmu_name) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xe6932195, __VMLINUX_SYMBOL_STR(hrtimer_start_range_ns) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x625e6bc, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0xb1e6a9a, __VMLINUX_SYMBOL_STR(kill_litter_super) },
	{ 0x25ca05b8, __VMLINUX_SYMBOL_STR(default_llseek) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0x4e001ade, __VMLINUX_SYMBOL_STR(get_task_mm) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xcba1c24c, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x838b13e7, __VMLINUX_SYMBOL_STR(ring_buffer_free) },
	{ 0x4e3024ae, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xb1dd70d3, __VMLINUX_SYMBOL_STR(simple_open) },
	{ 0xe299b8ed, __VMLINUX_SYMBOL_STR(__cpuhp_setup_state) },
	{ 0x3e3ec986, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0x75b9f0e4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x134e5d91, __VMLINUX_SYMBOL_STR(ring_buffer_event_length) },
	{ 0x81bd518d, __VMLINUX_SYMBOL_STR(find_vma) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xc188670f, __VMLINUX_SYMBOL_STR(simple_dir_operations) },
	{ 0x7729cbdd, __VMLINUX_SYMBOL_STR(task_handoff_register) },
	{ 0xfd305341, __VMLINUX_SYMBOL_STR(walk_stackframe) },
	{ 0x58d2273e, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xb4f518d6, __VMLINUX_SYMBOL_STR(get_mm_exe_file) },
	{ 0xafec7eba, __VMLINUX_SYMBOL_STR(flush_delayed_work) },
	{ 0xc0a98385, __VMLINUX_SYMBOL_STR(profile_pc) },
	{ 0x2c81ec75, __VMLINUX_SYMBOL_STR(__irq_regs) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x3fa6b28c, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0xe953b21f, __VMLINUX_SYMBOL_STR(get_next_ino) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x15726cd2, __VMLINUX_SYMBOL_STR(current_time) },
	{ 0xce58dc69, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x989729e2, __VMLINUX_SYMBOL_STR(get_dcookie) },
	{ 0xa12520d6, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0xa7d13249, __VMLINUX_SYMBOL_STR(simple_statfs) },
	{ 0x6157b761, __VMLINUX_SYMBOL_STR(d_alloc_name) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xa389a49a, __VMLINUX_SYMBOL_STR(profile_event_register) },
	{ 0xd6acb2c1, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0xdc89468, __VMLINUX_SYMBOL_STR(perf_event_create_kernel_counter) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x4a7aa211, __VMLINUX_SYMBOL_STR(new_inode) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x5541ea93, __VMLINUX_SYMBOL_STR(on_each_cpu) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x1de7591, __VMLINUX_SYMBOL_STR(simple_dir_inode_operations) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0x548179f7, __VMLINUX_SYMBOL_STR(ring_buffer_lock_reserve) },
	{ 0x74ef051e, __VMLINUX_SYMBOL_STR(ring_buffer_unlock_commit) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CB62927A6930D9138FAC99B");
