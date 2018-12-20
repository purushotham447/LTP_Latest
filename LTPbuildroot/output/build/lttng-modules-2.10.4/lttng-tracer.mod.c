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

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6d662533, __VMLINUX_SYMBOL_STR(_find_first_bit_le) },
	{ 0x90e32429, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x246f4157, __VMLINUX_SYMBOL_STR(tracepoint_probe_register) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xef03566e, __VMLINUX_SYMBOL_STR(for_each_kernel_tracepoint) },
	{ 0x7aa1756e, __VMLINUX_SYMBOL_STR(kvfree) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xe0c6f5f0, __VMLINUX_SYMBOL_STR(lib_ring_buffer_splice_read) },
	{ 0x41fc8b39, __VMLINUX_SYMBOL_STR(perf_event_release_kernel) },
	{ 0xca9c4dbb, __VMLINUX_SYMBOL_STR(lib_ring_buffer_clear_quiescent_channel) },
	{ 0x2068e934, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xd2cf12d3, __VMLINUX_SYMBOL_STR(lttng_kretprobes_unregister) },
	{ 0xf038f471, __VMLINUX_SYMBOL_STR(lttng_trace_clock) },
	{ 0x7dda30af, __VMLINUX_SYMBOL_STR(unregister_tracepoint_module_notifier) },
	{ 0x34e0e3c9, __VMLINUX_SYMBOL_STR(lttng_kprobes_destroy_private) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xb2a1b3c, __VMLINUX_SYMBOL_STR(lib_ring_buffer_set_quiescent_channel) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x6462a844, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xbc795a, __VMLINUX_SYMBOL_STR(lttng_kprobes_unregister) },
	{ 0xa843805a, __VMLINUX_SYMBOL_STR(get_unused_fd_flags) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xf01618ef, __VMLINUX_SYMBOL_STR(lib_ring_buffer_file_operations) },
	{ 0xbad565d1, __VMLINUX_SYMBOL_STR(vfs_lib_ring_buffer_no_llseek) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x407136b1, __VMLINUX_SYMBOL_STR(__put_user_8) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x8cbc1c26, __VMLINUX_SYMBOL_STR(lib_ring_buffer_release) },
	{ 0xd627480b, __VMLINUX_SYMBOL_STR(strncat) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5d825747, __VMLINUX_SYMBOL_STR(lttng_statedump_start) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0x58f14cfb, __VMLINUX_SYMBOL_STR(lttng_kretprobes_register) },
	{ 0x8450b494, __VMLINUX_SYMBOL_STR(__cpuhp_state_add_instance) },
	{ 0x4e8bfb05, __VMLINUX_SYMBOL_STR(lib_ring_buffer_lost_event_too_big) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x7c228d48, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0x5c017464, __VMLINUX_SYMBOL_STR(kvasprintf) },
	{ 0xe64a3c45, __VMLINUX_SYMBOL_STR(lib_ring_buffer_mmap) },
	{ 0xe007de41, __VMLINUX_SYMBOL_STR(kallsyms_lookup_name) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0xedbf1afc, __VMLINUX_SYMBOL_STR(__task_pid_nr_ns) },
	{ 0xd0e9299, __VMLINUX_SYMBOL_STR(lttng_ftrace_destroy_private) },
	{ 0xcd1611f8, __VMLINUX_SYMBOL_STR(lttng_ftrace_register) },
	{ 0x52f30bf0, __VMLINUX_SYMBOL_STR(lttng_clock_ref) },
	{ 0x88288e85, __VMLINUX_SYMBOL_STR(kvmalloc_node) },
	{ 0x2965d972, __VMLINUX_SYMBOL_STR(lttng_ftrace_unregister) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xe829057, __VMLINUX_SYMBOL_STR(lttng_kprobes_register) },
	{ 0x24709f1b, __VMLINUX_SYMBOL_STR(lib_ring_buffer_switch_slow) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x9a4cb0e0, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xd9ce8f0c, __VMLINUX_SYMBOL_STR(strnlen) },
	{ 0x8a7d1c31, __VMLINUX_SYMBOL_STR(high_memory) },
	{ 0x9fd3a319, __VMLINUX_SYMBOL_STR(__cpuhp_state_remove_instance) },
	{ 0x94eea794, __VMLINUX_SYMBOL_STR(getnstimeofday64) },
	{ 0x3f4547a7, __VMLINUX_SYMBOL_STR(put_unused_fd) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xbc072131, __VMLINUX_SYMBOL_STR(lttng_clock_unref) },
	{ 0x73ad200d, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x5f487a65, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x502297b2, __VMLINUX_SYMBOL_STR(lib_ring_buffer_ioctl) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x63115f0d, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0xefa2c27d, __VMLINUX_SYMBOL_STR(register_tracepoint_module_notifier) },
	{ 0x6c3f70e0, __VMLINUX_SYMBOL_STR(guid_gen) },
	{ 0xdc89468, __VMLINUX_SYMBOL_STR(perf_event_create_kernel_counter) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8296f8de, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0x398883e8, __VMLINUX_SYMBOL_STR(lttng_kretprobes_event_enable_state) },
	{ 0x3278dbe8, __VMLINUX_SYMBOL_STR(lib_ring_buffer_open) },
	{ 0xec3d2e1b, __VMLINUX_SYMBOL_STR(trace_hardirqs_off) },
	{ 0x1ecf6f99, __VMLINUX_SYMBOL_STR(anon_inode_getfile) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x33e56e8a, __VMLINUX_SYMBOL_STR(get_user_pages_fast) },
	{ 0x6d6fce3a, __VMLINUX_SYMBOL_STR(tracepoint_probe_unregister) },
	{ 0x16f04c2b, __VMLINUX_SYMBOL_STR(filp_open) },
	{ 0x818830bc, __VMLINUX_SYMBOL_STR(lttng_kretprobes_destroy_private) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lttng-lib-ring-buffer,lttng-kretprobes,lttng-clock,lttng-kprobes,lttng-statedump,lttng-ftrace";


MODULE_INFO(srcversion, "CE507FE2336E049B1EA1DFD");
