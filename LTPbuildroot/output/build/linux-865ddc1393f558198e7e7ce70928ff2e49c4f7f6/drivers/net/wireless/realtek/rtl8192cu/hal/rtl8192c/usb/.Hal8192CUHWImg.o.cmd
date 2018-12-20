cmd_drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o := /usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc -Wp,-MD,drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/.Hal8192CUHWImg.o.d  -nostdinc -isystem /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include -I./arch/arm/include -I./arch/arm/include/generated  -I./include -I./arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-PIE -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -O2 --param=allow-store-data-races=0 -DCC_HAVE_ASM_GOTO -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-merge-all-constants -fmerge-constants -fno-stack-check -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -O1 -Wall -Wextra -Werror=date-time -Werror=incompatible-pointer-types -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Wno-sign-compare -Wno-missing-field-initializers -Idrivers/net/wireless/realtek/rtl8192cu/include -DCONFIG_POWER_SAVING -DCONFIG_LITTLE_ENDIAN  -DMODULE  -DKBUILD_BASENAME='"Hal8192CUHWImg"'  -DKBUILD_MODNAME='"8192cu"' -c -o drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/.tmp_Hal8192CUHWImg.o drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.c

source_drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o := drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.c

deps_drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o := \
    $(wildcard include/config/bt/coexistence.h) \
  include/linux/compiler_types.h \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/gcov/kernel.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  drivers/net/wireless/realtek/rtl8192cu/include/basic_types.h \
  drivers/net/wireless/realtek/rtl8192cu/include/drv_conf.h \
    $(wildcard include/config/android.h) \
    $(wildcard include/config/platform/android.h) \
    $(wildcard include/config/validate/ssid.h) \
    $(wildcard include/config/signal/display/dbm.h) \
    $(wildcard include/config/has/earlysuspend.h) \
    $(wildcard include/config/resume/in/workqueue.h) \
    $(wildcard include/config/android/power.h) \
    $(wildcard include/config/wakelock.h) \
    $(wildcard include/config/usb/vendor/req/buffer/prealloc.h) \
    $(wildcard include/config/usb/vendor/req/mutex.h) \
    $(wildcard include/config/vendor/req/retry.h) \
  drivers/net/wireless/realtek/rtl8192cu/include/autoconf.h \
    $(wildcard include/config/usb/hci.h) \
    $(wildcard include/config/rtl8192c.h) \
    $(wildcard include/config/ioctl/cfg80211.h) \
    $(wildcard include/config/cfg80211/force/compatible/2/6/37/under.h) \
    $(wildcard include/config/debug/cfg80211.h) \
    $(wildcard include/config/drv/issue/prov/req.h) \
    $(wildcard include/config/set/scan/deny/timer.h) \
    $(wildcard include/config/pwrctrl.h) \
    $(wildcard include/config/h2clbk.h) \
    $(wildcard include/config/embedded/fwimg.h) \
    $(wildcard include/config/file/fwimg.h) \
    $(wildcard include/config/wake/on/wlan.h) \
    $(wildcard include/config/wowlan.h) \
    $(wildcard include/config/r871x/test.h) \
    $(wildcard include/config/xmit/ack.h) \
    $(wildcard include/config/xmit/ack/polling.h) \
    $(wildcard include/config/active/keep/alive/check.h) \
    $(wildcard include/config/80211n/ht.h) \
    $(wildcard include/config/recv/reordering/ctrl.h) \
    $(wildcard include/config/tcp/csum/offload/rx.h) \
    $(wildcard include/config/before/linked/dig.h) \
    $(wildcard include/config/drvext.h) \
    $(wildcard include/config/mp/included.h) \
    $(wildcard include/config/ips.h) \
    $(wildcard include/config/ips/level/2.h) \
    $(wildcard include/config/lps.h) \
    $(wildcard include/config/bt/coexist.h) \
    $(wildcard include/config/antenna/diversity.h) \
    $(wildcard include/config/sw/antenna/diversity.h) \
    $(wildcard include/config/hw/antenna/diversity.h) \
    $(wildcard include/config/iol.h) \
    $(wildcard include/config/mp/iwpriv/support.h) \
    $(wildcard include/config/ap/mode.h) \
    $(wildcard include/config/nativeap/mlme.h) \
    $(wildcard include/config/hostapd/mlme.h) \
    $(wildcard include/config/find/best/channel.h) \
    $(wildcard include/config/no/wireless/handlers.h) \
    $(wildcard include/config/p2p.h) \
    $(wildcard include/config/wfd.h) \
    $(wildcard include/config/wifi/test.h) \
    $(wildcard include/config/p2p/remove/group/info.h) \
    $(wildcard include/config/dbg/p2p.h) \
    $(wildcard include/config/p2p/ps.h) \
    $(wildcard include/config/p2p/ips.h) \
    $(wildcard include/config/tdls.h) \
    $(wildcard include/config/tdls/autosetup.h) \
    $(wildcard include/config/tdls/autocheckalive.h) \
    $(wildcard include/config/skb/copy.h) \
    $(wildcard include/config/led.h) \
    $(wildcard include/config/sw/led.h) \
    $(wildcard include/config/led/handled/by/cmd/thread.h) \
    $(wildcard include/config/global/ui/pid.h) \
    $(wildcard include/config/layer2/roaming.h) \
    $(wildcard include/config/layer2/roaming/resume.h) \
    $(wildcard include/config/adaptor/info/caching/file.h) \
    $(wildcard include/config/long/delay/issue.h) \
    $(wildcard include/config/new/signal/stat/process.h) \
    $(wildcard include/config/deauth/before/connect.h) \
    $(wildcard include/config/iol/llt.h) \
    $(wildcard include/config/iol/mac.h) \
    $(wildcard include/config/iol/bb/phy/reg.h) \
    $(wildcard include/config/iol/bb/agc/tab.h) \
    $(wildcard include/config/iol/rf/rf90/path/a.h) \
    $(wildcard include/config/iol/rf/rf90/path/b.h) \
    $(wildcard include/config/br/ext.h) \
    $(wildcard include/config/br/ext/brname.h) \
    $(wildcard include/config/tx/mcast2uni.h) \
    $(wildcard include/config/dm/adaptivity.h) \
    $(wildcard include/config/check/ac/lifetime.h) \
    $(wildcard include/config/concurrent/mode.h) \
    $(wildcard include/config/tsf/reset/offload.h) \
    $(wildcard include/config/hwport/swap.h) \
    $(wildcard include/config/sta/mode/scan/under/ap/mode.h) \
    $(wildcard include/config/multi/vir/ifaces.h) \
    $(wildcard include/config/80211d.h) \
    $(wildcard include/config/usb/one/out/ep.h) \
    $(wildcard include/config/usb/interrupt/in/pipe.h) \
    $(wildcard include/config/minimal/memory/usage.h) \
    $(wildcard include/config/usb/tx/aggregation.h) \
    $(wildcard include/config/usb/rx/aggregation.h) \
    $(wildcard include/config/prealloc/recv/skb.h) \
    $(wildcard include/config/reduce/usb/tx/int.h) \
    $(wildcard include/config/easy/replacement.h) \
    $(wildcard include/config/use/usb/buffer/alloc/xx.h) \
    $(wildcard include/config/use/usb/buffer/alloc/tx.h) \
    $(wildcard include/config/use/usb/buffer/alloc/rx.h) \
    $(wildcard include/config/usb/vendor/req/buffer/dynamic/allocate.h) \
    $(wildcard include/config/usb/support/async/vdn/req.h) \
    $(wildcard include/config/only/one/out/ep/to/low.h) \
    $(wildcard include/config/out/ep/wifi/mode.h) \
    $(wildcard include/config/platform/mn10300.h) \
    $(wildcard include/config/special/setting/for/funai/tv.h) \
    $(wildcard include/config/wistron/platform.h) \
    $(wildcard include/config/platform/ti/dm365.h) \
    $(wildcard include/config/attempt/to/fix/ap/beacon/error.h) \
    $(wildcard include/config/debug/rtl871x.h) \
    $(wildcard include/config/debug/rtl819x.h) \
    $(wildcard include/config/proc/debug.h) \
    $(wildcard include/config/error/detect.h) \
    $(wildcard include/config/error/reset.h) \
    $(wildcard include/config/single/xmit/buf.h) \
    $(wildcard include/config/single/recv/buf.h) \
    $(wildcard include/config/busy/traffic/skip/pwr/track.h) \
  include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  arch/arm/include/uapi/asm/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  arch/arm/include/uapi/asm/posix_types.h \
  include/uapi/asm-generic/posix_types.h \
  drivers/net/wireless/realtek/rtl8192cu/include/Hal8192CUHWImg.h \

drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o: $(deps_drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o)

$(deps_drivers/net/wireless/realtek/rtl8192cu/hal/rtl8192c/usb/Hal8192CUHWImg.o):
