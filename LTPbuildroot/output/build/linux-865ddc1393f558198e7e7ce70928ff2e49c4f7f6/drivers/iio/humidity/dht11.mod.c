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
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xfb807d84, __VMLINUX_SYMBOL_STR(devm_iio_device_register) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x93de854a, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xb6c1e257, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0x5a367e48, __VMLINUX_SYMBOL_STR(devm_gpio_request_one) },
	{ 0xaae6c7b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xd892e08d, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x689e06e, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xf64a8ce, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xeae1a7ec, __VMLINUX_SYMBOL_STR(wait_for_completion_killable_timeout) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x211c4d53, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x5be5f04e, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0xbaeef7b0, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xf3f18238, __VMLINUX_SYMBOL_STR(ktime_get_resolution_ns) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xac9657d8, __VMLINUX_SYMBOL_STR(ktime_get_with_offset) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio";

MODULE_ALIAS("of:N*T*Cdht11");
MODULE_ALIAS("of:N*T*Cdht11C*");

MODULE_INFO(srcversion, "46C425AE4FC99CB8BB3FF6F");
