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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x5c05dfa1, __VMLINUX_SYMBOL_STR(__mark_inode_dirty) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x269d63fd, __VMLINUX_SYMBOL_STR(ocfs2_cluster_disconnect) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x203f96ca, __VMLINUX_SYMBOL_STR(simple_lookup) },
	{ 0xc95887f2, __VMLINUX_SYMBOL_STR(generic_delete_inode) },
	{ 0xcdc49e19, __VMLINUX_SYMBOL_STR(lockref_get) },
	{ 0x346ce609, __VMLINUX_SYMBOL_STR(inc_nlink) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x424241c9, __VMLINUX_SYMBOL_STR(ocfs2_dlm_lvb) },
	{ 0x59188613, __VMLINUX_SYMBOL_STR(igrab) },
	{ 0x25ec616a, __VMLINUX_SYMBOL_STR(mount_nodev) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb1e6a9a, __VMLINUX_SYMBOL_STR(kill_litter_super) },
	{ 0x25ca05b8, __VMLINUX_SYMBOL_STR(default_llseek) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x7c228d48, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x165b69b2, __VMLINUX_SYMBOL_STR(setattr_copy) },
	{ 0x316904e1, __VMLINUX_SYMBOL_STR(ocfs2_dlm_unlock) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x60f4bcef, __VMLINUX_SYMBOL_STR(ocfs2_dlm_lvb_valid) },
	{ 0x40718c92, __VMLINUX_SYMBOL_STR(ocfs2_dlm_lock) },
	{ 0x3fe8e644, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0xd6e04bb7, __VMLINUX_SYMBOL_STR(simple_getattr) },
	{ 0x11736b03, __VMLINUX_SYMBOL_STR(__mlog_printk) },
	{ 0x9a4cb0e0, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xe40cffce, __VMLINUX_SYMBOL_STR(ocfs2_stack_glue_set_max_proto_version) },
	{ 0xb01865b7, __VMLINUX_SYMBOL_STR(simple_unlink) },
	{ 0xc188670f, __VMLINUX_SYMBOL_STR(simple_dir_operations) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x73ad200d, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x3fa6b28c, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xe953b21f, __VMLINUX_SYMBOL_STR(get_next_ino) },
	{ 0x344cb83a, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x15726cd2, __VMLINUX_SYMBOL_STR(current_time) },
	{ 0x3bcef5f3, __VMLINUX_SYMBOL_STR(ocfs2_dlm_lock_status) },
	{ 0xa12520d6, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0xa7d13249, __VMLINUX_SYMBOL_STR(simple_statfs) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xd6acb2c1, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xa06fbc10, __VMLINUX_SYMBOL_STR(ocfs2_cluster_connect_agnostic) },
	{ 0x4a7aa211, __VMLINUX_SYMBOL_STR(new_inode) },
	{ 0xf1e2057a, __VMLINUX_SYMBOL_STR(clear_inode) },
	{ 0x655e5b8, __VMLINUX_SYMBOL_STR(d_instantiate) },
	{ 0x218e3157, __VMLINUX_SYMBOL_STR(simple_rmdir) },
	{ 0xcaf3b277, __VMLINUX_SYMBOL_STR(setattr_prepare) },
	{ 0x362f3b0d, __VMLINUX_SYMBOL_STR(inode_init_owner) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ocfs2_stackglue,ocfs2_nodemanager";


MODULE_INFO(srcversion, "81527BECEAFE68D278B86FA");
