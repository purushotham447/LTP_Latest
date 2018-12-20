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
	{ 0x67db99b8, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xeb571a81, __VMLINUX_SYMBOL_STR(arizona_clk32k_enable) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x7fd3db2d, __VMLINUX_SYMBOL_STR(device_property_present) },
	{ 0x1cda20a2, __VMLINUX_SYMBOL_STR(device_property_read_u32_array) },
	{ 0xf7286b9e, __VMLINUX_SYMBOL_STR(gpiod_get_optional) },
	{ 0xa2daccc9, __VMLINUX_SYMBOL_STR(arizona_request_irq) },
	{ 0xd8b9dad3, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x34903431, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x5a367e48, __VMLINUX_SYMBOL_STR(devm_gpio_request_one) },
	{ 0x9853fdd0, __VMLINUX_SYMBOL_STR(devm_input_allocate_device) },
	{ 0x7a2fd55c, __VMLINUX_SYMBOL_STR(devm_extcon_dev_register) },
	{ 0x8030d90d, __VMLINUX_SYMBOL_STR(devm_extcon_dev_allocate) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xc9b9eb52, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xe03b8e24, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value_cansleep) },
	{ 0xbaeef7b0, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x13cae825, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x19b5ca8d, __VMLINUX_SYMBOL_STR(extcon_get_state) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x58d2273e, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x47884890, __VMLINUX_SYMBOL_STR(system_power_efficient_wq) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xff3e3628, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0x7ddd4f86, __VMLINUX_SYMBOL_STR(extcon_set_state_sync) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x4e692427, __VMLINUX_SYMBOL_STR(regulator_allow_bypass) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0xd500b853, __VMLINUX_SYMBOL_STR(__pm_runtime_suspend) },
	{ 0xc9078813, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x4dbb4a14, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0x5087703, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x37bcc140, __VMLINUX_SYMBOL_STR(snd_soc_component_disable_pin) },
	{ 0xe850c660, __VMLINUX_SYMBOL_STR(snd_soc_dapm_sync) },
	{ 0xf842b6b4, __VMLINUX_SYMBOL_STR(snd_soc_component_force_enable_pin) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7095faf8, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa603a59d, __VMLINUX_SYMBOL_STR(arizona_clk32k_disable) },
	{ 0xfd792e2a, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x5ac18032, __VMLINUX_SYMBOL_STR(arizona_free_irq) },
	{ 0xc65e8f41, __VMLINUX_SYMBOL_STR(arizona_set_irq_wake) },
	{ 0x870156c4, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x3434d1ad, __VMLINUX_SYMBOL_STR(gpiod_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=extcon-core,snd-soc-core";


MODULE_INFO(srcversion, "EA8E97E465838277BBD5811");
