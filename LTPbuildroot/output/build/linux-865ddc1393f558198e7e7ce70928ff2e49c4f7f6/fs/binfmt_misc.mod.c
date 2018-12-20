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
	{ 0xb1e6a9a, __VMLINUX_SYMBOL_STR(kill_litter_super) },
	{ 0xcba1c24c, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x25ca05b8, __VMLINUX_SYMBOL_STR(default_llseek) },
	{ 0xa7d13249, __VMLINUX_SYMBOL_STR(simple_statfs) },
	{ 0xd6acb2c1, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0x805a4ad3, __VMLINUX_SYMBOL_STR(unregister_binfmt) },
	{ 0x6ecbc3f, __VMLINUX_SYMBOL_STR(__register_binfmt) },
	{ 0x3fa6b28c, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x344cb83a, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x655e5b8, __VMLINUX_SYMBOL_STR(d_instantiate) },
	{ 0x6e97bf0f, __VMLINUX_SYMBOL_STR(simple_pin_fs) },
	{ 0x15726cd2, __VMLINUX_SYMBOL_STR(current_time) },
	{ 0xe953b21f, __VMLINUX_SYMBOL_STR(get_next_ino) },
	{ 0x4a7aa211, __VMLINUX_SYMBOL_STR(new_inode) },
	{ 0xb63c1e4c, __VMLINUX_SYMBOL_STR(lookup_one_len) },
	{ 0xc8339e24, __VMLINUX_SYMBOL_STR(string_unescape) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x3e3ec986, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0x75b9f0e4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xdc1a78c, __VMLINUX_SYMBOL_STR(bin2hex) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0x62d9fe29, __VMLINUX_SYMBOL_STR(simple_release_fs) },
	{ 0xf15901de, __VMLINUX_SYMBOL_STR(d_drop) },
	{ 0x7f660e5a, __VMLINUX_SYMBOL_STR(drop_nlink) },
	{ 0xd100acbd, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xf1e2057a, __VMLINUX_SYMBOL_STR(clear_inode) },
	{ 0x6462a844, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0x31420ae5, __VMLINUX_SYMBOL_STR(simple_fill_super) },
	{ 0xc06fe746, __VMLINUX_SYMBOL_STR(mount_single) },
	{ 0x99f94b17, __VMLINUX_SYMBOL_STR(filp_clone_open) },
	{ 0xbf2b9e4c, __VMLINUX_SYMBOL_STR(kernel_read) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xdcb0349b, __VMLINUX_SYMBOL_STR(sys_close) },
	{ 0x8c74b2c6, __VMLINUX_SYMBOL_STR(would_dump) },
	{ 0x63115f0d, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0xa843805a, __VMLINUX_SYMBOL_STR(get_unused_fd_flags) },
	{ 0xd77f126b, __VMLINUX_SYMBOL_STR(dput) },
	{ 0xe4bc6e2a, __VMLINUX_SYMBOL_STR(search_binary_handler) },
	{ 0x261bb606, __VMLINUX_SYMBOL_STR(prepare_binprm) },
	{ 0x98997107, __VMLINUX_SYMBOL_STR(open_exec) },
	{ 0x2efb9481, __VMLINUX_SYMBOL_STR(bprm_change_interp) },
	{ 0x1a9465d5, __VMLINUX_SYMBOL_STR(copy_strings_kernel) },
	{ 0xaf6d7a1f, __VMLINUX_SYMBOL_STR(fput) },
	{ 0xbe8a55a3, __VMLINUX_SYMBOL_STR(remove_arg_zero) },
	{ 0xcdc49e19, __VMLINUX_SYMBOL_STR(lockref_get) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x9f984513, __VMLINUX_SYMBOL_STR(strrchr) },
	{ 0xb5198b77, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "03255027ED183D6F1EE9615");
