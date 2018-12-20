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
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc290cacb, __VMLINUX_SYMBOL_STR(usb_gstrings_attach) },
	{ 0x67ab9b5f, __VMLINUX_SYMBOL_STR(usb_free_all_descriptors) },
	{ 0xc2f3edb2, __VMLINUX_SYMBOL_STR(gserial_connect) },
	{ 0x88a577ab, __VMLINUX_SYMBOL_STR(usb_ep_disable) },
	{ 0xb9a38379, __VMLINUX_SYMBOL_STR(usb_ep_enable) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x92215052, __VMLINUX_SYMBOL_STR(usb_ep_queue) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xf749fec9, __VMLINUX_SYMBOL_STR(usb_ep_set_halt) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb205404e, __VMLINUX_SYMBOL_STR(usb_function_unregister) },
	{ 0x9801f929, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x96e84f2b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0x88d84b5, __VMLINUX_SYMBOL_STR(gserial_disconnect) },
	{ 0xe7d69110, __VMLINUX_SYMBOL_STR(gs_alloc_req) },
	{ 0xb665c3e8, __VMLINUX_SYMBOL_STR(config_group_init_type_name) },
	{ 0x33bfdca2, __VMLINUX_SYMBOL_STR(gserial_alloc_line) },
	{ 0x2a7d4194, __VMLINUX_SYMBOL_STR(usb_function_register) },
	{ 0x1d680fd7, __VMLINUX_SYMBOL_STR(config_ep_by_speed) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb6652875, __VMLINUX_SYMBOL_STR(gserial_free_line) },
	{ 0xbe2b40c, __VMLINUX_SYMBOL_STR(usb_assign_descriptors) },
	{ 0xaf347307, __VMLINUX_SYMBOL_STR(usb_interface_id) },
	{ 0x1003c8fe, __VMLINUX_SYMBOL_STR(gs_free_req) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,u_serial,udc-core";


MODULE_INFO(srcversion, "7CC48B777B25A1B6C6F3A20");
