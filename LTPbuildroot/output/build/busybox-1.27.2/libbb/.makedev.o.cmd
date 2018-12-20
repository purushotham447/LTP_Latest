cmd_libbb/makedev.o := /usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc -Wp,-MD,libbb/.makedev.o.d   -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.27.2)" -DBB_BT=AUTOCONF_TIMESTAMP -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -I/usr/src/output/host/bin/../arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/tirpc   -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Os     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(makedev)"  -D"KBUILD_MODNAME=KBUILD_STR(makedev)" -c -o libbb/makedev.o libbb/makedev.c

deps_libbb/makedev.o := \
  libbb/makedev.c \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/nommu.h) \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include-fixed/limits.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include-fixed/syslimits.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/limits.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/features.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_config.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/cdefs.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/posix1_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/local_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/limits.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_local_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/posix2_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/xopen_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/stdio_lim.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/byteswap.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/byteswap.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/byteswap-common.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/types.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/wordsize.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/typesizes.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/byteswap-16.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/endian.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/endian.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include/stdint.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/stdint.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include/stdbool.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/unistd.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/posix_opt.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_posix_opt.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/environments.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include/stddef.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/confname.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/getopt.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/sysmacros.h \

libbb/makedev.o: $(deps_libbb/makedev.o)

$(deps_libbb/makedev.o):
