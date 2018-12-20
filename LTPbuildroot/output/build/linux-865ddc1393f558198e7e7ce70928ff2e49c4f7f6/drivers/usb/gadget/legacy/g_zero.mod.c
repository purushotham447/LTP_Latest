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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c2e3421, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x5ee52022, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xff3e6bcb, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig_reset) },
	{ 0xe18754ca, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfc982daa, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x9801f929, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0xa38caae0, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x20889a64, __VMLINUX_SYMBOL_STR(usb_composite_overwrite_options) },
	{ 0x896fd2ee, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xbc719814, __VMLINUX_SYMBOL_STR(usb_composite_probe) },
	{ 0x10d2ba7a, __VMLINUX_SYMBOL_STR(usb_add_function) },
	{ 0x959cb20f, __VMLINUX_SYMBOL_STR(usb_gadget_wakeup) },
	{ 0x50fcbaab, __VMLINUX_SYMBOL_STR(usb_put_function) },
	{ 0x1fcb36af, __VMLINUX_SYMBOL_STR(usb_composite_unregister) },
	{ 0x17ba1e3c, __VMLINUX_SYMBOL_STR(usb_get_function) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3f74e0fc, __VMLINUX_SYMBOL_STR(usb_string_ids_tab) },
	{ 0x104c36e0, __VMLINUX_SYMBOL_STR(usb_add_config_only) },
	{ 0xb903147d, __VMLINUX_SYMBOL_STR(usb_get_function_instance) },
	{ 0x8d13991e, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,udc-core";


MODULE_INFO(srcversion, "124BBAEC06D72116CD699C4");
