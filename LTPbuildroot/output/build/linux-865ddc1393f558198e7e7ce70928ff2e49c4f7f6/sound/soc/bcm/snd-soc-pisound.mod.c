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
	{ 0x4e251c31, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0xcd613ee5, __VMLINUX_SYMBOL_STR(gpiod_direction_output) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xad6d813b, __VMLINUX_SYMBOL_STR(spi_setup) },
	{ 0x1e115c71, __VMLINUX_SYMBOL_STR(snd_rawmidi_set_ops) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x6e1d4372, __VMLINUX_SYMBOL_STR(snd_rawmidi_new) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x2c50f62d, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xa3209eb0, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_mask64) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xb59aba19, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_list) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdcab5c07, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x712eea95, __VMLINUX_SYMBOL_STR(snd_rawmidi_transmit_peek) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x211c4d53, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x7cd650de, __VMLINUX_SYMBOL_STR(spi_bus_type) },
	{ 0x3d776c16, __VMLINUX_SYMBOL_STR(snd_soc_unregister_card) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xdfd3dcaa, __VMLINUX_SYMBOL_STR(bus_find_device) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xdb6fe13, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_bclk_ratio) },
	{ 0xd28c8e92, __VMLINUX_SYMBOL_STR(snd_rawmidi_transmit_ack) },
	{ 0x3c35e63b, __VMLINUX_SYMBOL_STR(gpiod_unexport) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xed7fe89b, __VMLINUX_SYMBOL_STR(snd_ctl_new1) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x7b2c5370, __VMLINUX_SYMBOL_STR(gpiod_get_value) },
	{ 0xea1c42b3, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0xb14e8416, __VMLINUX_SYMBOL_STR(gpiod_export) },
	{ 0xb6c1e257, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0x81fc8a11, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_minmax) },
	{ 0x1198a435, __VMLINUX_SYMBOL_STR(gpiod_get_index) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8e49e81b, __VMLINUX_SYMBOL_STR(snd_ctl_add) },
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xa7fe1ea6, __VMLINUX_SYMBOL_STR(gpiod_set_value) },
	{ 0x566ea6f, __VMLINUX_SYMBOL_STR(snd_soc_register_card) },
	{ 0x3434d1ad, __VMLINUX_SYMBOL_STR(gpiod_put) },
	{ 0x4a3db2b2, __VMLINUX_SYMBOL_STR(snd_rawmidi_receive) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-rawmidi,snd-pcm,snd-soc-core,snd";

MODULE_ALIAS("of:N*T*Cblokaslabs,pisound");
MODULE_ALIAS("of:N*T*Cblokaslabs,pisoundC*");
MODULE_ALIAS("of:N*T*Cblokaslabs,pisound-spi");
MODULE_ALIAS("of:N*T*Cblokaslabs,pisound-spiC*");

MODULE_INFO(srcversion, "EC76D65A3A751EF6AC8EE79");
