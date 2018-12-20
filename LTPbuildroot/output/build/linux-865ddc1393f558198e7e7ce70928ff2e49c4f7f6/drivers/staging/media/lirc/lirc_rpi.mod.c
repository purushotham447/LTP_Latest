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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x13892368, __VMLINUX_SYMBOL_STR(lirc_dev_fop_close) },
	{ 0x97fdafde, __VMLINUX_SYMBOL_STR(lirc_dev_fop_open) },
	{ 0x3b081d23, __VMLINUX_SYMBOL_STR(lirc_dev_fop_poll) },
	{ 0x8ccc658e, __VMLINUX_SYMBOL_STR(lirc_dev_fop_read) },
	{ 0xd9eb8ddc, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x4dca738, __VMLINUX_SYMBOL_STR(lirc_unregister_driver) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x559e9b80, __VMLINUX_SYMBOL_STR(lirc_register_driver) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x39e0d40b, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0xd0964726, __VMLINUX_SYMBOL_STR(of_property_read_u32_index) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x87d2d145, __VMLINUX_SYMBOL_STR(gpiochip_find) },
	{ 0x6192ce5a, __VMLINUX_SYMBOL_STR(platform_device_put) },
	{ 0xba2873be, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0x5093815e, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x27363b8f, __VMLINUX_SYMBOL_STR(of_find_device_by_node) },
	{ 0x73fd9743, __VMLINUX_SYMBOL_STR(of_find_compatible_node) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xc068440e, __VMLINUX_SYMBOL_STR(__kfifo_alloc) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0xdb760f52, __VMLINUX_SYMBOL_STR(__kfifo_free) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x4e3024ae, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xbc477a2, __VMLINUX_SYMBOL_STR(irq_set_irq_type) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x4f68e5c9, __VMLINUX_SYMBOL_STR(do_gettimeofday) },
	{ 0xf23fcb99, __VMLINUX_SYMBOL_STR(__kfifo_in) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x94eea794, __VMLINUX_SYMBOL_STR(getnstimeofday64) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xe2e8065e, __VMLINUX_SYMBOL_STR(memdup_user) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xb0b00bb3, __VMLINUX_SYMBOL_STR(lirc_dev_fop_ioctl) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lirc_dev";

MODULE_ALIAS("of:N*T*Crpi,lirc-rpi");
MODULE_ALIAS("of:N*T*Crpi,lirc-rpiC*");

MODULE_INFO(srcversion, "6357677E18F4047B7C10001");
