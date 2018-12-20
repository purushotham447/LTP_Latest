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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe93e49c3, __VMLINUX_SYMBOL_STR(devres_free) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x70e632a3, __VMLINUX_SYMBOL_STR(iio_kfifo_allocate) },
	{ 0x19465956, __VMLINUX_SYMBOL_STR(devres_alloc_node) },
	{ 0x7f70fb4b, __VMLINUX_SYMBOL_STR(devm_iio_device_match) },
	{ 0x6c6ae64a, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x4861d89e, __VMLINUX_SYMBOL_STR(iio_device_attach_buffer) },
	{ 0x1a7883f, __VMLINUX_SYMBOL_STR(devres_release) },
	{ 0x5d03e104, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0x71db564a, __VMLINUX_SYMBOL_STR(iio_kfifo_free) },
	{ 0x588913b2, __VMLINUX_SYMBOL_STR(devres_add) },
	{ 0x86019ae, __VMLINUX_SYMBOL_STR(iio_alloc_pollfunc) },
	{ 0xd1000fb6, __VMLINUX_SYMBOL_STR(iio_dealloc_pollfunc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=kfifo_buf,industrialio";


MODULE_INFO(srcversion, "E6C701783AF27252026FF9B");
