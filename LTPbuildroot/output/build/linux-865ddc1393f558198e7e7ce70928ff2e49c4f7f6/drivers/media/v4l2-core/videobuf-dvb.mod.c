#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd12b1c71, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0x9e077512, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0xd3c0a269, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0xfd967d49, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x432799ca, __VMLINUX_SYMBOL_STR(dvb_net_release) },
	{ 0x27168320, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xf10c395e, __VMLINUX_SYMBOL_STR(dvb_frontend_detach) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x2e053047, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0x220b31be, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf14c5dcc, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xd5c2f403, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
	{ 0x518ec665, __VMLINUX_SYMBOL_STR(dvb_net_init) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x300a2687, __VMLINUX_SYMBOL_STR(videobuf_read_start) },
	{ 0xb554a437, __VMLINUX_SYMBOL_STR(dvb_dmx_release) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0xf4bfa21, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x4eb1234e, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x981afc69, __VMLINUX_SYMBOL_STR(videobuf_waiton) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0x1a59b856, __VMLINUX_SYMBOL_STR(videobuf_queue_to_vaddr) },
	{ 0x2ada471a, __VMLINUX_SYMBOL_STR(videobuf_read_stop) },
	{ 0x1ee7392b, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dvb-core,videobuf-core";


MODULE_INFO(srcversion, "4C862AF13411F103F8384E0");
