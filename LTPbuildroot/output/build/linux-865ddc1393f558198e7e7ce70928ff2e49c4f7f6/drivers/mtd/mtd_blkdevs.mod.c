#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
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
	{ 0xfc032b9d, __VMLINUX_SYMBOL_STR(blk_init_queue) },
	{ 0x34f80151, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xf0e0a296, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xbde07469, __VMLINUX_SYMBOL_STR(mtd_table_mutex) },
	{ 0x6088cca4, __VMLINUX_SYMBOL_STR(rq_flush_dcache_pages) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x411e8d12, __VMLINUX_SYMBOL_STR(__put_mtd_device) },
	{ 0xfb26edc8, __VMLINUX_SYMBOL_STR(blk_start_queue) },
	{ 0x884c8d30, __VMLINUX_SYMBOL_STR(__get_mtd_device) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x456913ac, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x7f23a6b3, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdcab5c07, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x88a6ee07, __VMLINUX_SYMBOL_STR(blk_queue_max_discard_sectors) },
	{ 0xf5a03b27, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xaad7f970, __VMLINUX_SYMBOL_STR(register_mtd_user) },
	{ 0xdd87d63a, __VMLINUX_SYMBOL_STR(__mtd_next_device) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x97154aa, __VMLINUX_SYMBOL_STR(unregister_mtd_user) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xa412e273, __VMLINUX_SYMBOL_STR(blk_queue_bounce_limit) },
	{ 0x154c7db9, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x243d9108, __VMLINUX_SYMBOL_STR(__blk_end_request_cur) },
	{ 0x99a00e1b, __VMLINUX_SYMBOL_STR(blk_fetch_request) },
	{ 0x9de8addd, __VMLINUX_SYMBOL_STR(__blk_end_request_all) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2492d879, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0x1126f883, __VMLINUX_SYMBOL_STR(blk_queue_write_cache) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x6282e515, __VMLINUX_SYMBOL_STR(device_add_disk) },
	{ 0x1163f0a7, __VMLINUX_SYMBOL_STR(blk_max_low_pfn) },
	{ 0xed63fa6b, __VMLINUX_SYMBOL_STR(blk_queue_logical_block_size) },
	{ 0x337a2a75, __VMLINUX_SYMBOL_STR(set_disk_ro) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mtd";


MODULE_INFO(srcversion, "F32407F9BE20AAC79789D65");
