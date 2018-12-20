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
	{ 0xc1a84bab, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0xbc02d511, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0xa44b9436, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x4124ced2, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0xdc044e36, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x77e71afb, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x4620712e, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x85ded073, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x7a02a0bd, __VMLINUX_SYMBOL_STR(__netlink_dump_start) },
	{ 0xb2aa467f, __VMLINUX_SYMBOL_STR(crypto_alg_mod_lookup) },
	{ 0x71a6a18, __VMLINUX_SYMBOL_STR(crypto_unregister_instance) },
	{ 0x3de9cae1, __VMLINUX_SYMBOL_STR(crypto_remove_final) },
	{ 0x74fce698, __VMLINUX_SYMBOL_STR(crypto_mod_put) },
	{ 0x3e3ec986, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa755ce12, __VMLINUX_SYMBOL_STR(crypto_remove_spawns) },
	{ 0x75b9f0e4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xd9ce8f0c, __VMLINUX_SYMBOL_STR(strnlen) },
	{ 0xe439a287, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x219842cb, __VMLINUX_SYMBOL_STR(crypto_mod_get) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x67d487a2, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x404dd171, __VMLINUX_SYMBOL_STR(crypto_alg_sem) },
	{ 0x457594fa, __VMLINUX_SYMBOL_STR(crypto_alg_list) },
	{ 0x18650c66, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x5bd0748f, __VMLINUX_SYMBOL_STR(crypto_del_default_rng) },
	{ 0x15b3ba88, __VMLINUX_SYMBOL_STR(netlink_capable) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x24bc2fb9, __VMLINUX_SYMBOL_STR(netlink_rcv_skb) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7C0E590C337EB70DCD88A77");
