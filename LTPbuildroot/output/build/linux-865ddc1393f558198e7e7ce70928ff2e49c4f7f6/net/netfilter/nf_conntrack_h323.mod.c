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
	{ 0x9ab82b9f, __VMLINUX_SYMBOL_STR(nf_ct_remove_expectations) },
	{ 0x6ba7c8a3, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0xa3faa39c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x9585935a, __VMLINUX_SYMBOL_STR(nf_conntrack_helper_register) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf137b376, __VMLINUX_SYMBOL_STR(__nf_ct_refresh_acct) },
	{ 0x4bad5bbe, __VMLINUX_SYMBOL_STR(nf_conntrack_helper_unregister) },
	{ 0x55f6dde4, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x257dda3d, __VMLINUX_SYMBOL_STR(nf_ct_expect_init) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x93a5f065, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x305be44, __VMLINUX_SYMBOL_STR(nf_conntrack_helpers_register) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x6892b89d, __VMLINUX_SYMBOL_STR(nf_ct_expect_put) },
	{ 0xbbd18f77, __VMLINUX_SYMBOL_STR(nf_ct_expect_alloc) },
	{ 0x86703d9b, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0x31ffe4b9, __VMLINUX_SYMBOL_STR(nf_conntrack_helpers_unregister) },
	{ 0x7050fd8d, __VMLINUX_SYMBOL_STR(__nf_ct_expect_find) },
	{ 0xc2abd2fd, __VMLINUX_SYMBOL_STR(nf_conntrack_expect_lock) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x6fd1cdbe, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0xb352ea44, __VMLINUX_SYMBOL_STR(nf_afinfo) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5ae8f300, __VMLINUX_SYMBOL_STR(mod_timer_pending) },
	{ 0xe7d71645, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack";


MODULE_INFO(srcversion, "E524F08D41CB9C3F9F7AFEC");
