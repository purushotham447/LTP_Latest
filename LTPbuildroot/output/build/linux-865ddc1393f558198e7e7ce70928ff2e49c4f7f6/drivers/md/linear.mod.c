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
	{ 0xb869ebfe, __VMLINUX_SYMBOL_STR(bio_chain) },
	{ 0xcfe0785a, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0x938999db, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x7958f0b5, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0x3ee589e2, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0xff771bd, __VMLINUX_SYMBOL_STR(__cpu_online_mask) },
	{ 0xd2e9487e, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x36ba63a3, __VMLINUX_SYMBOL_STR(__tracepoint_block_bio_remap) },
	{ 0xcf79de0a, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0xdef8376b, __VMLINUX_SYMBOL_STR(md_check_no_bitmap) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x7a2e807f, __VMLINUX_SYMBOL_STR(revalidate_disk) },
	{ 0x722613d8, __VMLINUX_SYMBOL_STR(mddev_resume) },
	{ 0x35c0dec1, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0xb97075c2, __VMLINUX_SYMBOL_STR(mddev_suspend) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x9e4d251, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";


MODULE_INFO(srcversion, "22ED3737757747A6FFEE308");
