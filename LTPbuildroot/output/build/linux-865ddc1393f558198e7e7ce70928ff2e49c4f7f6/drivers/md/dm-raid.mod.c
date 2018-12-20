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
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x416652b9, __VMLINUX_SYMBOL_STR(dm_unregister_target) },
	{ 0x9a36162d, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0x357d754e, __VMLINUX_SYMBOL_STR(raid5_set_cache_size) },
	{ 0xcaf91eb5, __VMLINUX_SYMBOL_STR(r5c_journal_mode_set) },
	{ 0xb1425b32, __VMLINUX_SYMBOL_STR(dm_table_add_target_callbacks) },
	{ 0xc25e5773, __VMLINUX_SYMBOL_STR(md_run) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xcf0a03b0, __VMLINUX_SYMBOL_STR(dm_set_target_max_io_len) },
	{ 0x252ca82e, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0x373db350, __VMLINUX_SYMBOL_STR(kstrtoint) },
	{ 0xb1f304df, __VMLINUX_SYMBOL_STR(md_rdev_init) },
	{ 0x258fcedb, __VMLINUX_SYMBOL_STR(mddev_init) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x11e0ec41, __VMLINUX_SYMBOL_STR(dm_read_arg) },
	{ 0x7deff673, __VMLINUX_SYMBOL_STR(dm_consume_args) },
	{ 0xc7d094b5, __VMLINUX_SYMBOL_STR(dm_read_arg_group) },
	{ 0x5eb24829, __VMLINUX_SYMBOL_STR(dm_shift_arg) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x4be85a03, __VMLINUX_SYMBOL_STR(memweight) },
	{ 0x2ab9a0a4, __VMLINUX_SYMBOL_STR(bitmap_resize) },
	{ 0xa2e3d58a, __VMLINUX_SYMBOL_STR(bitmap_load) },
	{ 0x98e06e0b, __VMLINUX_SYMBOL_STR(mddev_unlock) },
	{ 0x706c4c74, __VMLINUX_SYMBOL_STR(md_update_sb) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x722613d8, __VMLINUX_SYMBOL_STR(mddev_resume) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xd4b07b71, __VMLINUX_SYMBOL_STR(md_error) },
	{ 0xd0ab4b6f, __VMLINUX_SYMBOL_STR(sync_page_io) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xad84bef8, __VMLINUX_SYMBOL_STR(dm_table_event) },
	{ 0x40a38876, __VMLINUX_SYMBOL_STR(mddev_congested) },
	{ 0xf0994ec0, __VMLINUX_SYMBOL_STR(md_stop) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x94ab1673, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0xbca40680, __VMLINUX_SYMBOL_STR(md_rdev_clear) },
	{ 0xe9ec075a, __VMLINUX_SYMBOL_STR(md_handle_request) },
	{ 0xf7573b46, __VMLINUX_SYMBOL_STR(md_stop_writes) },
	{ 0xb97075c2, __VMLINUX_SYMBOL_STR(mddev_suspend) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x7a2e807f, __VMLINUX_SYMBOL_STR(revalidate_disk) },
	{ 0x24a467e9, __VMLINUX_SYMBOL_STR(dm_disk) },
	{ 0x3abde0fa, __VMLINUX_SYMBOL_STR(dm_table_get_md) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xf2f55e18, __VMLINUX_SYMBOL_STR(md_reap_sync_thread) },
	{ 0x2fb2c9f0, __VMLINUX_SYMBOL_STR(md_wakeup_thread) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0x8ab20d42, __VMLINUX_SYMBOL_STR(blk_limits_io_opt) },
	{ 0xad64a9d6, __VMLINUX_SYMBOL_STR(blk_limits_io_min) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod,raid456,md-mod";


MODULE_INFO(srcversion, "B2A7D80DFAFF4712E4EDB65");
