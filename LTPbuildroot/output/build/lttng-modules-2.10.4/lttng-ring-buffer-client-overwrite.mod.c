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

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xc20e3628, __VMLINUX_SYMBOL_STR(lttng_transport_unregister) },
	{ 0x47503cd7, __VMLINUX_SYMBOL_STR(lttng_transport_register) },
	{ 0xe007de41, __VMLINUX_SYMBOL_STR(kallsyms_lookup_name) },
	{ 0xc46a9f8b, __VMLINUX_SYMBOL_STR(lib_ring_buffer_reserve_slow) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x7adeb8d4, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0xf038f471, __VMLINUX_SYMBOL_STR(lttng_trace_clock) },
	{ 0x997d395a, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa5d02a55, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x436a50f, __VMLINUX_SYMBOL_STR(channel_create) },
	{ 0x4c7d4caa, __VMLINUX_SYMBOL_STR(channel_destroy) },
	{ 0xe8fd210c, __VMLINUX_SYMBOL_STR(lib_ring_buffer_open_read) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xc7b3c757, __VMLINUX_SYMBOL_STR(lib_ring_buffer_release_read) },
	{ 0x333d74ac, __VMLINUX_SYMBOL_STR(lib_ring_buffer_check_deliver_slow) },
	{ 0x2776a3e5, __VMLINUX_SYMBOL_STR(lib_ring_buffer_nesting) },
	{ 0x26d10481, __VMLINUX_SYMBOL_STR(_lib_ring_buffer_write) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x56b4141, __VMLINUX_SYMBOL_STR(_lib_ring_buffer_copy_from_user_inatomic) },
	{ 0x96e9c8d6, __VMLINUX_SYMBOL_STR(_lib_ring_buffer_strcpy) },
	{ 0x36fc10be, __VMLINUX_SYMBOL_STR(_lib_ring_buffer_strcpy_from_user_inatomic) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x66239fb, __VMLINUX_SYMBOL_STR(_lib_ring_buffer_memset) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x4a198a26, __VMLINUX_SYMBOL_STR(lib_ring_buffer_offset_address) },
	{ 0xa686b1e7, __VMLINUX_SYMBOL_STR(channel_get_ring_buffer) },
	{ 0xba369518, __VMLINUX_SYMBOL_STR(lib_ring_buffer_read_offset_address) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lttng-tracer,lttng-lib-ring-buffer,lttng-clock";


MODULE_INFO(srcversion, "945A27D025970E32A989220");
