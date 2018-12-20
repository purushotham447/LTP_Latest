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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa5483b26, __VMLINUX_SYMBOL_STR(irlmp_data_request) },
	{ 0x541a63f, __VMLINUX_SYMBOL_STR(irlmp_open_lsap) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2068e934, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0x33cbe2c6, __VMLINUX_SYMBOL_STR(proc_irda) },
	{ 0xc58a2516, __VMLINUX_SYMBOL_STR(irttp_close_tsap) },
	{ 0xe640823c, __VMLINUX_SYMBOL_STR(irlmp_close_lsap) },
	{ 0xf34c039a, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xf13a6c95, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xca99424e, __VMLINUX_SYMBOL_STR(irttp_connect_request) },
	{ 0x36849e0f, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xaca3ef98, __VMLINUX_SYMBOL_STR(irttp_data_request) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x5992cea, __VMLINUX_SYMBOL_STR(irlmp_connect_response) },
	{ 0x5c480b34, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xd697e69a, __VMLINUX_SYMBOL_STR(trace_hardirqs_on) },
	{ 0x2aad97a4, __VMLINUX_SYMBOL_STR(irlmp_disconnect_request) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x53a31a8c, __VMLINUX_SYMBOL_STR(irttp_disconnect_request) },
	{ 0x8a44dd5e, __VMLINUX_SYMBOL_STR(hashbin_new) },
	{ 0x6b76aa70, __VMLINUX_SYMBOL_STR(hashbin_delete) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x90ddb6bd, __VMLINUX_SYMBOL_STR(hashbin_remove) },
	{ 0x6492e28c, __VMLINUX_SYMBOL_STR(hashbin_get_next) },
	{ 0xd8477f69, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xc144892b, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x9ddce5c3, __VMLINUX_SYMBOL_STR(irttp_connect_response) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x37791344, __VMLINUX_SYMBOL_STR(hashbin_get_first) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x9ee0f7a1, __VMLINUX_SYMBOL_STR(irda_notify_init) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xb449a1c7, __VMLINUX_SYMBOL_STR(irlmp_connect_request) },
	{ 0x6d36d466, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd4a61d2c, __VMLINUX_SYMBOL_STR(irttp_open_tsap) },
	{ 0xbfa7c08d, __VMLINUX_SYMBOL_STR(hashbin_lock_find) },
	{ 0x8296f8de, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0xfaaa86c8, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x2a628db, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0x4fbf9662, __VMLINUX_SYMBOL_STR(irttp_flow_request) },
	{ 0x731cec71, __VMLINUX_SYMBOL_STR(hashbin_insert) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=irda";


MODULE_INFO(srcversion, "2393236B8EC50AEE6CC225A");
