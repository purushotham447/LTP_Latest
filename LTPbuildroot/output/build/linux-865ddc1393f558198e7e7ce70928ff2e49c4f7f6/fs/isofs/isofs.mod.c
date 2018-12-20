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
	{ 0x90e32429, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x102fb6c2, __VMLINUX_SYMBOL_STR(iget_failed) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xcfea3d4a, __VMLINUX_SYMBOL_STR(sb_min_blocksize) },
	{ 0x107e5878, __VMLINUX_SYMBOL_STR(zlib_inflateEnd) },
	{ 0xf3e8c2c1, __VMLINUX_SYMBOL_STR(unload_nls) },
	{ 0x74ae2835, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xddb422af, __VMLINUX_SYMBOL_STR(iget5_locked) },
	{ 0x497d23ba, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x194eecc3, __VMLINUX_SYMBOL_STR(pagecache_get_page) },
	{ 0xacf4d843, __VMLINUX_SYMBOL_STR(match_strdup) },
	{ 0xdf5d41e2, __VMLINUX_SYMBOL_STR(ll_rw_block) },
	{ 0xcae232b, __VMLINUX_SYMBOL_STR(utf16s_to_utf8s) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x6833b73d, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0xfb2f8a4, __VMLINUX_SYMBOL_STR(mktime64) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x519ea3f9, __VMLINUX_SYMBOL_STR(mount_bdev) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x305988e3, __VMLINUX_SYMBOL_STR(page_symlink_inode_operations) },
	{ 0xb83c133, __VMLINUX_SYMBOL_STR(generic_read_dir) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xa28d8a44, __VMLINUX_SYMBOL_STR(__getblk_gfp) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x73f261ac, __VMLINUX_SYMBOL_STR(from_kgid_munged) },
	{ 0x305a3e4e, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0xd6ab5e84, __VMLINUX_SYMBOL_STR(mpage_readpages) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x623e8c4c, __VMLINUX_SYMBOL_STR(mpage_readpage) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0xcad4ddf0, __VMLINUX_SYMBOL_STR(__bread_gfp) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x15f3efa9, __VMLINUX_SYMBOL_STR(d_obtain_alias) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xce5ac24f, __VMLINUX_SYMBOL_STR(zlib_inflate_workspacesize) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x7c228d48, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9571e650, __VMLINUX_SYMBOL_STR(set_nlink) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x82e75679, __VMLINUX_SYMBOL_STR(__wait_on_buffer) },
	{ 0xdd27fa87, __VMLINUX_SYMBOL_STR(memchr) },
	{ 0xb4ddef4d, __VMLINUX_SYMBOL_STR(generic_ro_fops) },
	{ 0x4e3567f7, __VMLINUX_SYMBOL_STR(match_int) },
	{ 0x3a144c1d, __VMLINUX_SYMBOL_STR(unlock_page) },
	{ 0xa999f3d1, __VMLINUX_SYMBOL_STR(inode_nohighmem) },
	{ 0x2b28cb7e, __VMLINUX_SYMBOL_STR(__brelse) },
	{ 0x581f98da, __VMLINUX_SYMBOL_STR(zlib_inflate) },
	{ 0x3fe8e644, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0x9a4cb0e0, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0xaa6f383, __VMLINUX_SYMBOL_STR(load_nls) },
	{ 0x2aa0e4fc, __VMLINUX_SYMBOL_STR(strncasecmp) },
	{ 0xb363791b, __VMLINUX_SYMBOL_STR(unlock_new_inode) },
	{ 0xaa10593, __VMLINUX_SYMBOL_STR(kill_block_super) },
	{ 0x800fb92b, __VMLINUX_SYMBOL_STR(full_name_hash) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x73ad200d, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x3fa6b28c, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x35a88f28, __VMLINUX_SYMBOL_STR(zlib_inflateInit2) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0x344cb83a, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x49bbe1ae, __VMLINUX_SYMBOL_STR(load_nls_default) },
	{ 0xed775c78, __VMLINUX_SYMBOL_STR(d_splice_alias) },
	{ 0x8046f2f8, __VMLINUX_SYMBOL_STR(sync_filesystem) },
	{ 0x7bc7d026, __VMLINUX_SYMBOL_STR(sb_set_blocksize) },
	{ 0xa12520d6, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0x40bc53b1, __VMLINUX_SYMBOL_STR(ioctl_by_bdev) },
	{ 0xd6acb2c1, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0x4cb96dc2, __VMLINUX_SYMBOL_STR(init_special_inode) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x8d09056, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0xd3187f21, __VMLINUX_SYMBOL_STR(generic_block_bmap) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "60C6D480795D6DF69C4B995");
