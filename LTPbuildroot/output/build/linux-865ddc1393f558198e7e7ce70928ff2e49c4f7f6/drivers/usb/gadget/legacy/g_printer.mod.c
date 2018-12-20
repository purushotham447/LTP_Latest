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
	{ 0x7124b618, __VMLINUX_SYMBOL_STR(usb_add_config) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xff3e6bcb, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig_reset) },
	{ 0xe18754ca, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x9801f929, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x20889a64, __VMLINUX_SYMBOL_STR(usb_composite_overwrite_options) },
	{ 0xbc719814, __VMLINUX_SYMBOL_STR(usb_composite_probe) },
	{ 0x10d2ba7a, __VMLINUX_SYMBOL_STR(usb_add_function) },
	{ 0x50fcbaab, __VMLINUX_SYMBOL_STR(usb_put_function) },
	{ 0x38a5bc57, __VMLINUX_SYMBOL_STR(usb_gadget_set_selfpowered) },
	{ 0x1fcb36af, __VMLINUX_SYMBOL_STR(usb_composite_unregister) },
	{ 0x17ba1e3c, __VMLINUX_SYMBOL_STR(usb_get_function) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3f74e0fc, __VMLINUX_SYMBOL_STR(usb_string_ids_tab) },
	{ 0xb903147d, __VMLINUX_SYMBOL_STR(usb_get_function_instance) },
	{ 0x8d13991e, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,udc-core";


MODULE_INFO(srcversion, "CD45D1BA09FEF7968FE871C");
