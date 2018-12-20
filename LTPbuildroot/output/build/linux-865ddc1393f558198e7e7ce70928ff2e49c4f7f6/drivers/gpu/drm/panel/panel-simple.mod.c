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
	{ 0x934c6be5, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x552dced5, __VMLINUX_SYMBOL_STR(mipi_dsi_driver_unregister) },
	{ 0x84e12845, __VMLINUX_SYMBOL_STR(mipi_dsi_driver_register_full) },
	{ 0x24218f92, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x4dbb4a14, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xf935cb84, __VMLINUX_SYMBOL_STR(mipi_dsi_detach) },
	{ 0x83db54a5, __VMLINUX_SYMBOL_STR(drm_panel_remove) },
	{ 0x20938f59, __VMLINUX_SYMBOL_STR(drm_panel_detach) },
	{ 0xc9078813, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x2389640d, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xda7c0bcf, __VMLINUX_SYMBOL_STR(mipi_dsi_attach) },
	{ 0x71caaac6, __VMLINUX_SYMBOL_STR(of_match_node) },
	{ 0xc6a3c9e9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xbc6cda7, __VMLINUX_SYMBOL_STR(drm_panel_add) },
	{ 0x17cd620d, __VMLINUX_SYMBOL_STR(drm_panel_init) },
	{ 0xfede52fa, __VMLINUX_SYMBOL_STR(of_find_i2c_adapter_by_node) },
	{ 0x442a4fc4, __VMLINUX_SYMBOL_STR(of_node_put) },
	{ 0x6922d1fe, __VMLINUX_SYMBOL_STR(of_find_backlight_by_node) },
	{ 0x1a63d5ea, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x429a2edd, __VMLINUX_SYMBOL_STR(devm_gpiod_get_optional) },
	{ 0xc9b9eb52, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0x16396722, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xe6782faf, __VMLINUX_SYMBOL_STR(drm_display_info_set_bus_formats) },
	{ 0xbe0e636d, __VMLINUX_SYMBOL_STR(drm_mode_set_name) },
	{ 0xd20f60d2, __VMLINUX_SYMBOL_STR(drm_mode_duplicate) },
	{ 0x534dd61c, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x508e9898, __VMLINUX_SYMBOL_STR(drm_mode_create) },
	{ 0x8e1f209e, __VMLINUX_SYMBOL_STR(videomode_from_timing) },
	{ 0xc197bf4c, __VMLINUX_SYMBOL_STR(drm_mode_probed_add) },
	{ 0x29f1e700, __VMLINUX_SYMBOL_STR(drm_display_mode_from_videomode) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x646bc1c3, __VMLINUX_SYMBOL_STR(drm_add_edid_modes) },
	{ 0x48e8b4d4, __VMLINUX_SYMBOL_STR(drm_mode_connector_update_edid_property) },
	{ 0xb14f9c5e, __VMLINUX_SYMBOL_STR(drm_get_edid) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm";

MODULE_ALIAS("of:N*T*Cauo,b080uan01");
MODULE_ALIAS("of:N*T*Cauo,b080uan01C*");
MODULE_ALIAS("of:N*T*Cboe,tv080wum-nl0");
MODULE_ALIAS("of:N*T*Cboe,tv080wum-nl0C*");
MODULE_ALIAS("of:N*T*Clg,ld070wx3-sl01");
MODULE_ALIAS("of:N*T*Clg,ld070wx3-sl01C*");
MODULE_ALIAS("of:N*T*Clg,lh500wx1-sd03");
MODULE_ALIAS("of:N*T*Clg,lh500wx1-sd03C*");
MODULE_ALIAS("of:N*T*Cpanasonic,vvx10f004b00");
MODULE_ALIAS("of:N*T*Cpanasonic,vvx10f004b00C*");
MODULE_ALIAS("of:N*T*Campire,am-480272h3tmqw-t01h");
MODULE_ALIAS("of:N*T*Campire,am-480272h3tmqw-t01hC*");
MODULE_ALIAS("of:N*T*Campire,am800480r3tmqwa1h");
MODULE_ALIAS("of:N*T*Campire,am800480r3tmqwa1hC*");
MODULE_ALIAS("of:N*T*Cauo,b101aw03");
MODULE_ALIAS("of:N*T*Cauo,b101aw03C*");
MODULE_ALIAS("of:N*T*Cauo,b101ean01");
MODULE_ALIAS("of:N*T*Cauo,b101ean01C*");
MODULE_ALIAS("of:N*T*Cauo,b101xtn01");
MODULE_ALIAS("of:N*T*Cauo,b101xtn01C*");
MODULE_ALIAS("of:N*T*Cauo,b116xw03");
MODULE_ALIAS("of:N*T*Cauo,b116xw03C*");
MODULE_ALIAS("of:N*T*Cauo,b133htn01");
MODULE_ALIAS("of:N*T*Cauo,b133htn01C*");
MODULE_ALIAS("of:N*T*Cauo,b133xtn01");
MODULE_ALIAS("of:N*T*Cauo,b133xtn01C*");
MODULE_ALIAS("of:N*T*Cauo,g133han01");
MODULE_ALIAS("of:N*T*Cauo,g133han01C*");
MODULE_ALIAS("of:N*T*Cauo,g185han01");
MODULE_ALIAS("of:N*T*Cauo,g185han01C*");
MODULE_ALIAS("of:N*T*Cauo,p320hvn03");
MODULE_ALIAS("of:N*T*Cauo,p320hvn03C*");
MODULE_ALIAS("of:N*T*Cauo,t215hvn01");
MODULE_ALIAS("of:N*T*Cauo,t215hvn01C*");
MODULE_ALIAS("of:N*T*Cavic,tm070ddh03");
MODULE_ALIAS("of:N*T*Cavic,tm070ddh03C*");
MODULE_ALIAS("of:N*T*Cboe,nv101wxmn51");
MODULE_ALIAS("of:N*T*Cboe,nv101wxmn51C*");
MODULE_ALIAS("of:N*T*Cchunghwa,claa070wp03xg");
MODULE_ALIAS("of:N*T*Cchunghwa,claa070wp03xgC*");
MODULE_ALIAS("of:N*T*Cchunghwa,claa101wa01a");
MODULE_ALIAS("of:N*T*Cchunghwa,claa101wa01aC*");
MODULE_ALIAS("of:N*T*Cchunghwa,claa101wb01");
MODULE_ALIAS("of:N*T*Cchunghwa,claa101wb01C*");
MODULE_ALIAS("of:N*T*Cedt,et057090dhu");
MODULE_ALIAS("of:N*T*Cedt,et057090dhuC*");
MODULE_ALIAS("of:N*T*Cedt,et070080dh6");
MODULE_ALIAS("of:N*T*Cedt,et070080dh6C*");
MODULE_ALIAS("of:N*T*Cedt,etm0700g0dh6");
MODULE_ALIAS("of:N*T*Cedt,etm0700g0dh6C*");
MODULE_ALIAS("of:N*T*Cfoxlink,fl500wvr00-a0t");
MODULE_ALIAS("of:N*T*Cfoxlink,fl500wvr00-a0tC*");
MODULE_ALIAS("of:N*T*Cgiantplus,gpg482739qs5");
MODULE_ALIAS("of:N*T*Cgiantplus,gpg482739qs5C*");
MODULE_ALIAS("of:N*T*Channstar,hsd070pww1");
MODULE_ALIAS("of:N*T*Channstar,hsd070pww1C*");
MODULE_ALIAS("of:N*T*Channstar,hsd100pxn1");
MODULE_ALIAS("of:N*T*Channstar,hsd100pxn1C*");
MODULE_ALIAS("of:N*T*Chit,tx23d38vm0caa");
MODULE_ALIAS("of:N*T*Chit,tx23d38vm0caaC*");
MODULE_ALIAS("of:N*T*Cinnolux,at043tn24");
MODULE_ALIAS("of:N*T*Cinnolux,at043tn24C*");
MODULE_ALIAS("of:N*T*Cinnolux,at070tn92");
MODULE_ALIAS("of:N*T*Cinnolux,at070tn92C*");
MODULE_ALIAS("of:N*T*Cinnolux,g101ice-l01");
MODULE_ALIAS("of:N*T*Cinnolux,g101ice-l01C*");
MODULE_ALIAS("of:N*T*Cinnolux,g121i1-l01");
MODULE_ALIAS("of:N*T*Cinnolux,g121i1-l01C*");
MODULE_ALIAS("of:N*T*Cinnolux,g121x1-l03");
MODULE_ALIAS("of:N*T*Cinnolux,g121x1-l03C*");
MODULE_ALIAS("of:N*T*Cinnolux,n116bge");
MODULE_ALIAS("of:N*T*Cinnolux,n116bgeC*");
MODULE_ALIAS("of:N*T*Cinnolux,n156bge-l21");
MODULE_ALIAS("of:N*T*Cinnolux,n156bge-l21C*");
MODULE_ALIAS("of:N*T*Cinnolux,zj070na-01p");
MODULE_ALIAS("of:N*T*Cinnolux,zj070na-01pC*");
MODULE_ALIAS("of:N*T*Ckyo,tcg121xglp");
MODULE_ALIAS("of:N*T*Ckyo,tcg121xglpC*");
MODULE_ALIAS("of:N*T*Clg,lb070wv8");
MODULE_ALIAS("of:N*T*Clg,lb070wv8C*");
MODULE_ALIAS("of:N*T*Clg,lp079qx1-sp0v");
MODULE_ALIAS("of:N*T*Clg,lp079qx1-sp0vC*");
MODULE_ALIAS("of:N*T*Clg,lp097qx1-spa1");
MODULE_ALIAS("of:N*T*Clg,lp097qx1-spa1C*");
MODULE_ALIAS("of:N*T*Clg,lp120up1");
MODULE_ALIAS("of:N*T*Clg,lp120up1C*");
MODULE_ALIAS("of:N*T*Clg,lp129qe");
MODULE_ALIAS("of:N*T*Clg,lp129qeC*");
MODULE_ALIAS("of:N*T*Cnec,nl12880bc20-05");
MODULE_ALIAS("of:N*T*Cnec,nl12880bc20-05C*");
MODULE_ALIAS("of:N*T*Cnec,nl4827hc19-05b");
MODULE_ALIAS("of:N*T*Cnec,nl4827hc19-05bC*");
MODULE_ALIAS("of:N*T*Cnetron-dy,e231732");
MODULE_ALIAS("of:N*T*Cnetron-dy,e231732C*");
MODULE_ALIAS("of:N*T*Cnlt,nl192108ac18-02d");
MODULE_ALIAS("of:N*T*Cnlt,nl192108ac18-02dC*");
MODULE_ALIAS("of:N*T*Cnvd,9128");
MODULE_ALIAS("of:N*T*Cnvd,9128C*");
MODULE_ALIAS("of:N*T*Cokaya,rs800480t-7x0gp");
MODULE_ALIAS("of:N*T*Cokaya,rs800480t-7x0gpC*");
MODULE_ALIAS("of:N*T*Colimex,lcd-olinuxino-43-ts");
MODULE_ALIAS("of:N*T*Colimex,lcd-olinuxino-43-tsC*");
MODULE_ALIAS("of:N*T*Contat,yx700wv03");
MODULE_ALIAS("of:N*T*Contat,yx700wv03C*");
MODULE_ALIAS("of:N*T*Cortustech,com43h4m85ulc");
MODULE_ALIAS("of:N*T*Cortustech,com43h4m85ulcC*");
MODULE_ALIAS("of:N*T*Cqiaodian,qd43003c0-40");
MODULE_ALIAS("of:N*T*Cqiaodian,qd43003c0-40C*");
MODULE_ALIAS("of:N*T*Csamsung,lsn122dl01-c01");
MODULE_ALIAS("of:N*T*Csamsung,lsn122dl01-c01C*");
MODULE_ALIAS("of:N*T*Csamsung,ltn101nt05");
MODULE_ALIAS("of:N*T*Csamsung,ltn101nt05C*");
MODULE_ALIAS("of:N*T*Csamsung,ltn140at29-301");
MODULE_ALIAS("of:N*T*Csamsung,ltn140at29-301C*");
MODULE_ALIAS("of:N*T*Csharp,lq101k1ly04");
MODULE_ALIAS("of:N*T*Csharp,lq101k1ly04C*");
MODULE_ALIAS("of:N*T*Csharp,lq123p1jx31");
MODULE_ALIAS("of:N*T*Csharp,lq123p1jx31C*");
MODULE_ALIAS("of:N*T*Csharp,lq150x1lg11");
MODULE_ALIAS("of:N*T*Csharp,lq150x1lg11C*");
MODULE_ALIAS("of:N*T*Cshelly,sca07010-bfn-lnn");
MODULE_ALIAS("of:N*T*Cshelly,sca07010-bfn-lnnC*");
MODULE_ALIAS("of:N*T*Cstarry,kr122ea0sra");
MODULE_ALIAS("of:N*T*Cstarry,kr122ea0sraC*");
MODULE_ALIAS("of:N*T*Ctianma,tm070jdhg30");
MODULE_ALIAS("of:N*T*Ctianma,tm070jdhg30C*");
MODULE_ALIAS("of:N*T*Ctpk,f07a-0102");
MODULE_ALIAS("of:N*T*Ctpk,f07a-0102C*");
MODULE_ALIAS("of:N*T*Ctpk,f10a-0102");
MODULE_ALIAS("of:N*T*Ctpk,f10a-0102C*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-tC*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-1t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-1tC*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-7t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-7tC*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-11t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-11tC*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-19t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-19tC*");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-20t");
MODULE_ALIAS("of:N*T*Curt,umsh-8596md-20tC*");
MODULE_ALIAS("of:N*T*Cwinstar,wf35ltiacd");
MODULE_ALIAS("of:N*T*Cwinstar,wf35ltiacdC*");

MODULE_INFO(srcversion, "C4C12C3C634D093C767FA7B");
