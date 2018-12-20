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
	{ 0x22966dca, __VMLINUX_SYMBOL_STR(fuse_file_poll) },
	{ 0xcba1c24c, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x4c25efff, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0xad050f2b, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xc6486daf, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0x65961174, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x734eb085, __VMLINUX_SYMBOL_STR(fuse_dev_operations) },
	{ 0x8e830385, __VMLINUX_SYMBOL_STR(fuse_put_request) },
	{ 0xc50ad301, __VMLINUX_SYMBOL_STR(fuse_dev_free) },
	{ 0x6cf2038d, __VMLINUX_SYMBOL_STR(fuse_request_send_background) },
	{ 0x1820da81, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x363bc223, __VMLINUX_SYMBOL_STR(fuse_get_req_for_background) },
	{ 0x8ddb3d56, __VMLINUX_SYMBOL_STR(fuse_dev_alloc) },
	{ 0xf7f8f7d, __VMLINUX_SYMBOL_STR(fuse_conn_init) },
	{ 0xbfb4486c, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x67e64e02, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x9ea73f87, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x2f670f3d, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x398f1a2f, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x23fa0429, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd8e484f0, __VMLINUX_SYMBOL_STR(register_chrdev_region) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x77bc13a0, __VMLINUX_SYMBOL_STR(strim) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x9a84cce3, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x98059526, __VMLINUX_SYMBOL_STR(fuse_direct_io) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x4e3ce010, __VMLINUX_SYMBOL_STR(fuse_do_ioctl) },
	{ 0x76d7f1a, __VMLINUX_SYMBOL_STR(fuse_do_open) },
	{ 0xd4d8a38c, __VMLINUX_SYMBOL_STR(fuse_conn_get) },
	{ 0x2885f7c7, __VMLINUX_SYMBOL_STR(fuse_sync_release) },
	{ 0x19f462ab, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xce3523f0, __VMLINUX_SYMBOL_STR(fuse_dev_release) },
	{ 0x6d39fa18, __VMLINUX_SYMBOL_STR(fuse_conn_put) },
	{ 0x4ffb44fd, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xbe2701cc, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd37847be, __VMLINUX_SYMBOL_STR(fuse_abort_conn) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=fuse";


MODULE_INFO(srcversion, "5DA215AB4AE20021FC24E0F");
