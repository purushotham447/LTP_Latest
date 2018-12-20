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
	{ 0x28e2cb20, __VMLINUX_SYMBOL_STR(unregister_md_personality) },
	{ 0x76605447, __VMLINUX_SYMBOL_STR(register_md_personality) },
	{ 0x938999db, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xdaa24803, __VMLINUX_SYMBOL_STR(bio_clone_blkcg_association) },
	{ 0x5ca9657, __VMLINUX_SYMBOL_STR(__blkdev_issue_discard) },
	{ 0x3ee589e2, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0xb869ebfe, __VMLINUX_SYMBOL_STR(bio_chain) },
	{ 0xcfe0785a, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0xd2e9487e, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x36ba63a3, __VMLINUX_SYMBOL_STR(__tracepoint_block_bio_remap) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xcf79de0a, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0x35c0dec1, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0x9e4d251, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0xb5c9d50b, __VMLINUX_SYMBOL_STR(blk_queue_io_opt) },
	{ 0x1f414826, __VMLINUX_SYMBOL_STR(blk_queue_io_min) },
	{ 0x88a6ee07, __VMLINUX_SYMBOL_STR(blk_queue_max_discard_sectors) },
	{ 0xff4579e1, __VMLINUX_SYMBOL_STR(blk_queue_max_write_zeroes_sectors) },
	{ 0x9b59862b, __VMLINUX_SYMBOL_STR(blk_queue_max_write_same_sectors) },
	{ 0x70752a38, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0xdef8376b, __VMLINUX_SYMBOL_STR(md_check_no_bitmap) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x7958f0b5, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";


MODULE_INFO(srcversion, "37346C1C661795B1FADBC44");
