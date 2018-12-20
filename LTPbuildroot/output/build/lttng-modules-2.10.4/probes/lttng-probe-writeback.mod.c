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
	{ 0xe89155c9, __VMLINUX_SYMBOL_STR(lttng_probe_unregister) },
	{ 0xee98474c, __VMLINUX_SYMBOL_STR(lttng_probe_register) },
	{ 0x412d8816, __VMLINUX_SYMBOL_STR(vm_node_stat) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe007de41, __VMLINUX_SYMBOL_STR(kallsyms_lookup_name) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x168135, __VMLINUX_SYMBOL_STR(I_BDEV) },
	{ 0x785510cb, __VMLINUX_SYMBOL_STR(noop_backing_dev_info) },
	{ 0x53c7d350, __VMLINUX_SYMBOL_STR(blockdev_superblock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3ef53914, __VMLINUX_SYMBOL_STR(lttng_dynamic_len_stack) },
	{ 0xd2c8889e, __VMLINUX_SYMBOL_STR(lttng_pid_tracker_lookup) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lttng-tracer";


MODULE_INFO(srcversion, "E9992089CD50307F3F99B7F");
