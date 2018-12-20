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
	{ 0x62023715, __VMLINUX_SYMBOL_STR(xfrm6_protocol_register) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0x47141424, __VMLINUX_SYMBOL_STR(skb_to_sgvec) },
	{ 0x95dc1b95, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x41852aac, __VMLINUX_SYMBOL_STR(xfrm_unregister_type) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xd5152710, __VMLINUX_SYMBOL_STR(sg_next) },
	{ 0x987c11c7, __VMLINUX_SYMBOL_STR(__pv_phys_pfn_offset) },
	{ 0x8e9ba6a2, __VMLINUX_SYMBOL_STR(pskb_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0xdd04677f, __VMLINUX_SYMBOL_STR(skb_page_frag_refill) },
	{ 0xf26eb1c8, __VMLINUX_SYMBOL_STR(skb_cow_data) },
	{ 0xb7fc173a, __VMLINUX_SYMBOL_STR(ip6_redirect) },
	{ 0x7c5b837a, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xabfc0865, __VMLINUX_SYMBOL_STR(xfrm_input_resume) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfd934f04, __VMLINUX_SYMBOL_STR(skb_checksum) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbeef10b4, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xa6e66685, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byname) },
	{ 0x6333006e, __VMLINUX_SYMBOL_STR(crypto_aead_setkey) },
	{ 0xe63b4a26, __VMLINUX_SYMBOL_STR(xfrm_register_type) },
	{ 0x99120eee, __VMLINUX_SYMBOL_STR(xfrm6_find_1stfragopt) },
	{ 0xa814c582, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x3db8e0dd, __VMLINUX_SYMBOL_STR(xfrm_output_resume) },
	{ 0x574a92d1, __VMLINUX_SYMBOL_STR(ip6_update_pmtu) },
	{ 0xa616d7ef, __VMLINUX_SYMBOL_STR(skb_pull_rcsum) },
	{ 0xa23400b1, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0x4b8cb8b5, __VMLINUX_SYMBOL_STR(crypto_aead_setauthsize) },
	{ 0xc9fea2, __VMLINUX_SYMBOL_STR(crypto_alloc_aead) },
	{ 0x9f82eb6e, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xff3d718f, __VMLINUX_SYMBOL_STR(___pskb_trim) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0xa39472b5, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xb5cbddc6, __VMLINUX_SYMBOL_STR(xfrm6_rcv) },
	{ 0x1a952a83, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0x5134edcb, __VMLINUX_SYMBOL_STR(xfrm6_protocol_deregister) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ipv6";


MODULE_INFO(srcversion, "21E32E9D33448EDC8519382");
