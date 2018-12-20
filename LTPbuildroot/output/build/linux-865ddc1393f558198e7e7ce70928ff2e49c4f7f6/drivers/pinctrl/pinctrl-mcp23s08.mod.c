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
	{ 0x2419e578, __VMLINUX_SYMBOL_STR(pinconf_generic_dt_free_map) },
	{ 0xc22e7785, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x1ac52327, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x79c26f50, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x7bd5aecd, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0x1cda20a2, __VMLINUX_SYMBOL_STR(device_property_read_u32_array) },
	{ 0xc35c284f, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0x809e3303, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x45cfd571, __VMLINUX_SYMBOL_STR(gpiochip_set_nested_irqchip) },
	{ 0x57829af1, __VMLINUX_SYMBOL_STR(gpiochip_irqchip_add_key) },
	{ 0x21465cea, __VMLINUX_SYMBOL_STR(handle_simple_irq) },
	{ 0x4acc6ca1, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0x7cae589a, __VMLINUX_SYMBOL_STR(__devm_regmap_init_i2c) },
	{ 0x64e4e5ff, __VMLINUX_SYMBOL_STR(devm_pinctrl_register) },
	{ 0xf6ddb523, __VMLINUX_SYMBOL_STR(devm_gpiochip_add_data) },
	{ 0x7fd3db2d, __VMLINUX_SYMBOL_STR(device_property_present) },
	{ 0x1f439fbc, __VMLINUX_SYMBOL_STR(__devm_regmap_init) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x549525ef, __VMLINUX_SYMBOL_STR(handle_nested_irq) },
	{ 0x8a3af137, __VMLINUX_SYMBOL_STR(irq_find_mapping) },
	{ 0xc293114f, __VMLINUX_SYMBOL_STR(regcache_sync) },
	{ 0xd08c099f, __VMLINUX_SYMBOL_STR(regcache_cache_only) },
	{ 0x78084a20, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x72451e7, __VMLINUX_SYMBOL_STR(gpiochip_is_requested) },
	{ 0xfa8e0169, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0x53817baa, __VMLINUX_SYMBOL_STR(regcache_cache_bypass) },
	{ 0xade989e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2d829396, __VMLINUX_SYMBOL_STR(gpiochip_get_data) },
	{ 0x18be8326, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xbcbdc44c, __VMLINUX_SYMBOL_STR(spi_write_then_read) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xa66c9b08, __VMLINUX_SYMBOL_STR(pinctrl_dev_get_drvdata) },
	{ 0x2a569e70, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3b89030b, __VMLINUX_SYMBOL_STR(pinconf_generic_dt_node_to_map) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("spi:mcp23s08");
MODULE_ALIAS("spi:mcp23s17");
MODULE_ALIAS("spi:mcp23s18");
MODULE_ALIAS("i2c:mcp23008");
MODULE_ALIAS("i2c:mcp23017");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23008");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23008C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23017");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23017C*");
MODULE_ALIAS("of:N*T*Cmcp,mcp23008");
MODULE_ALIAS("of:N*T*Cmcp,mcp23008C*");
MODULE_ALIAS("of:N*T*Cmcp,mcp23017");
MODULE_ALIAS("of:N*T*Cmcp,mcp23017C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s08");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s08C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s17");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s17C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s18");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp23s18C*");
MODULE_ALIAS("of:N*T*Cmcp,mcp23s08");
MODULE_ALIAS("of:N*T*Cmcp,mcp23s08C*");
MODULE_ALIAS("of:N*T*Cmcp,mcp23s17");
MODULE_ALIAS("of:N*T*Cmcp,mcp23s17C*");

MODULE_INFO(srcversion, "7DA736B0D4B5AD8B1D6B420");
