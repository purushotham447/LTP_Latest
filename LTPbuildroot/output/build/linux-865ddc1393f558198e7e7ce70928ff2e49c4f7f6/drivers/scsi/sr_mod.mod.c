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
	{ 0x7e36e87e, __VMLINUX_SYMBOL_STR(scsi_set_medium_removal) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf5fbdea6, __VMLINUX_SYMBOL_STR(blk_queue_rq_timeout) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x34f80151, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x860dc4e0, __VMLINUX_SYMBOL_STR(cdrom_number_of_slots) },
	{ 0xfe90c4a6, __VMLINUX_SYMBOL_STR(_find_first_zero_bit_le) },
	{ 0xf33b819d, __VMLINUX_SYMBOL_STR(scsi_ioctl_block_when_processing_errors) },
	{ 0xa4e9ffc9, __VMLINUX_SYMBOL_STR(unregister_cdrom) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x8d289084, __VMLINUX_SYMBOL_STR(blk_dump_rq_flags) },
	{ 0xd5152710, __VMLINUX_SYMBOL_STR(sg_next) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x20aca8ae, __VMLINUX_SYMBOL_STR(scmd_printk) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x81d1d6b3, __VMLINUX_SYMBOL_STR(cdrom_open) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc6b75c9a, __VMLINUX_SYMBOL_STR(scsi_execute) },
	{ 0xc932afdc, __VMLINUX_SYMBOL_STR(scsi_autopm_get_device) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x29a643ac, __VMLINUX_SYMBOL_STR(cdrom_release) },
	{ 0xf5a03b27, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x6bbda04a, __VMLINUX_SYMBOL_STR(sdev_prefix_printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x26f2e5e6, __VMLINUX_SYMBOL_STR(cdrom_get_media_event) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0xe2729e01, __VMLINUX_SYMBOL_STR(cdrom_check_events) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x9e159509, __VMLINUX_SYMBOL_STR(cdrom_get_last_written) },
	{ 0xf7f7ab8b, __VMLINUX_SYMBOL_STR(scsi_device_put) },
	{ 0xf920413b, __VMLINUX_SYMBOL_STR(scsi_ioctl) },
	{ 0x154c7db9, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x12917ca8, __VMLINUX_SYMBOL_STR(scsi_register_driver) },
	{ 0xa1978a24, __VMLINUX_SYMBOL_STR(scsi_block_when_processing_errors) },
	{ 0x710ec68d, __VMLINUX_SYMBOL_STR(scsi_test_unit_ready) },
	{ 0x5f0c1b33, __VMLINUX_SYMBOL_STR(scsi_init_io) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd7c39442, __VMLINUX_SYMBOL_STR(cdrom_ioctl) },
	{ 0x31cff25d, __VMLINUX_SYMBOL_STR(blk_pm_runtime_init) },
	{ 0x24200a4d, __VMLINUX_SYMBOL_STR(register_cdrom) },
	{ 0x6282e515, __VMLINUX_SYMBOL_STR(device_add_disk) },
	{ 0x7c3ec630, __VMLINUX_SYMBOL_STR(scsi_device_get) },
	{ 0x82cd602c, __VMLINUX_SYMBOL_STR(scsi_autopm_put_device) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xed63fa6b, __VMLINUX_SYMBOL_STR(blk_queue_logical_block_size) },
	{ 0x85d3f0d7, __VMLINUX_SYMBOL_STR(scsi_mode_sense) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cdrom";


MODULE_INFO(srcversion, "91D59DEDB6DBEAB90F84A5A");
