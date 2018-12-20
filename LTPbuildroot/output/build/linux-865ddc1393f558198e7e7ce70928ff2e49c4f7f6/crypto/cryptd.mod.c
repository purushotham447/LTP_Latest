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
	{ 0x6f3952e7, __VMLINUX_SYMBOL_STR(crypto_alloc_skcipher) },
	{ 0x43676a90, __VMLINUX_SYMBOL_STR(crypto_attr_alg2) },
	{ 0xa8109599, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xee6a6843, __VMLINUX_SYMBOL_STR(ahash_register_instance) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x6268077d, __VMLINUX_SYMBOL_STR(shash_attr_alg) },
	{ 0x74fce698, __VMLINUX_SYMBOL_STR(crypto_mod_put) },
	{ 0x97ae33d0, __VMLINUX_SYMBOL_STR(crypto_ablkcipher_type) },
	{ 0xcc8f97ed, __VMLINUX_SYMBOL_STR(crypto_dequeue_request) },
	{ 0x9a11a0fc, __VMLINUX_SYMBOL_STR(crypto_attr_alg_name) },
	{ 0x68dca8b4, __VMLINUX_SYMBOL_STR(shash_ahash_digest) },
	{ 0x755c32c, __VMLINUX_SYMBOL_STR(crypto_grab_skcipher) },
	{ 0x9d7e240c, __VMLINUX_SYMBOL_STR(crypto_unregister_template) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0xcfdd60c8, __VMLINUX_SYMBOL_STR(crypto_init_spawn) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x70a44bd, __VMLINUX_SYMBOL_STR(crypto_shash_final) },
	{ 0x1d0bc38a, __VMLINUX_SYMBOL_STR(crypto_spawn_tfm) },
	{ 0xa0add6e8, __VMLINUX_SYMBOL_STR(shash_ahash_finup) },
	{ 0xbc7118cf, __VMLINUX_SYMBOL_STR(skcipher_register_instance) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x4e810d22, __VMLINUX_SYMBOL_STR(cpumask_next) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x9cc0cba7, __VMLINUX_SYMBOL_STR(crypto_grab_aead) },
	{ 0xb45f2d4, __VMLINUX_SYMBOL_STR(__cpu_possible_mask) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0xc0304434, __VMLINUX_SYMBOL_STR(crypto_register_template) },
	{ 0xd4093cf7, __VMLINUX_SYMBOL_STR(crypto_register_instance) },
	{ 0x82c983c2, __VMLINUX_SYMBOL_STR(crypto_shash_setkey) },
	{ 0x499043d3, __VMLINUX_SYMBOL_STR(crypto_init_queue) },
	{ 0x2c1df36e, __VMLINUX_SYMBOL_STR(crypto_drop_spawn) },
	{ 0x6333006e, __VMLINUX_SYMBOL_STR(crypto_aead_setkey) },
	{ 0x124f2056, __VMLINUX_SYMBOL_STR(crypto_get_attr_type) },
	{ 0xdf954662, __VMLINUX_SYMBOL_STR(crypto_enqueue_request) },
	{ 0x3b46719f, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x2ce98559, __VMLINUX_SYMBOL_STR(kcrypto_wq) },
	{ 0xec1aa6ef, __VMLINUX_SYMBOL_STR(memzero_explicit) },
	{ 0x4c890c25, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x341dbfa3, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x4b8cb8b5, __VMLINUX_SYMBOL_STR(crypto_aead_setauthsize) },
	{ 0xc9fea2, __VMLINUX_SYMBOL_STR(crypto_alloc_aead) },
	{ 0x31b9195c, __VMLINUX_SYMBOL_STR(__local_bh_disable_ip) },
	{ 0xa95b2a8c, __VMLINUX_SYMBOL_STR(crypto_spawn_tfm2) },
	{ 0x663dd147, __VMLINUX_SYMBOL_STR(crypto_init_shash_spawn) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x2a12136, __VMLINUX_SYMBOL_STR(shash_ahash_update) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x9f957ae0, __VMLINUX_SYMBOL_STR(shash_no_setkey) },
	{ 0xa37e1a, __VMLINUX_SYMBOL_STR(crypto_alloc_base) },
	{ 0xfe59e551, __VMLINUX_SYMBOL_STR(aead_register_instance) },
	{ 0x9d0875c8, __VMLINUX_SYMBOL_STR(crypto_alloc_ahash) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "8980F74B87DE7D86B6D9DB8");
