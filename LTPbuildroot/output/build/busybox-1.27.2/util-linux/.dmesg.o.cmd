cmd_util-linux/dmesg.o := /usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc -Wp,-MD,util-linux/.dmesg.o.d   -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.27.2)" -DBB_BT=AUTOCONF_TIMESTAMP -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -I/usr/src/output/host/bin/../arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/tirpc   -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Os     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(dmesg)"  -D"KBUILD_MODNAME=KBUILD_STR(dmesg)" -c -o util-linux/dmesg.o util-linux/dmesg.c

deps_util-linux/dmesg.o := \
  util-linux/dmesg.c \
    $(wildcard include/config/dmesg.h) \
    $(wildcard include/config/feature/dmesg/pretty.h) \
    $(wildcard include/config/feature/clean/up.h) \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/klog.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/features.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_config.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/cdefs.h \
  include/libbb.h \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/use/bb/shadow.h) \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/feature/utmp.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/use/bb/pwd/grp.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/verbose.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/feature/seamless/xz.h) \
    $(wildcard include/config/feature/seamless/lzma.h) \
    $(wildcard include/config/feature/seamless/bz2.h) \
    $(wildcard include/config/feature/seamless/gz.h) \
    $(wildcard include/config/feature/seamless/z.h) \
    $(wildcard include/config/feature/check/names.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/long/opts.h) \
    $(wildcard include/config/feature/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/echo.h) \
    $(wildcard include/config/printf.h) \
    $(wildcard include/config/test.h) \
    $(wildcard include/config/test1.h) \
    $(wildcard include/config/test2.h) \
    $(wildcard include/config/kill.h) \
    $(wildcard include/config/killall.h) \
    $(wildcard include/config/killall5.h) \
    $(wildcard include/config/chown.h) \
    $(wildcard include/config/ls.h) \
    $(wildcard include/config/xxx.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/feature/hwib.h) \
    $(wildcard include/config/desktop.h) \
    $(wildcard include/config/feature/crond/d.h) \
    $(wildcard include/config/feature/securetty.h) \
    $(wildcard include/config/pam.h) \
    $(wildcard include/config/use/bb/crypt.h) \
    $(wildcard include/config/feature/adduser/to/group.h) \
    $(wildcard include/config/feature/del/user/from/group.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/feature/editing/save/on/exit.h) \
    $(wildcard include/config/pmap.h) \
    $(wildcard include/config/feature/show/threads.h) \
    $(wildcard include/config/feature/ps/additional/columns.h) \
    $(wildcard include/config/feature/topmem.h) \
    $(wildcard include/config/feature/top/smp/process.h) \
    $(wildcard include/config/pgrep.h) \
    $(wildcard include/config/pkill.h) \
    $(wildcard include/config/pidof.h) \
    $(wildcard include/config/sestatus.h) \
    $(wildcard include/config/unicode/support.h) \
    $(wildcard include/config/feature/mtab/support.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/nommu.h) \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include-fixed/limits.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include-fixed/syslimits.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/limits.h \
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
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/ctype.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_touplow.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/dirent.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/dirent.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/errno.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/errno.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/errno.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/errno.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/errno.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/errno-base.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/fcntl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/fcntl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/types.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/time.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/select.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/select.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sigset.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/time.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/sysmacros.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/pthreadtypes.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uio.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/stat.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/stat.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/inttypes.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/netdb.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/netinet/in.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/socket.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/uio.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/socket.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/socket_type.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sockaddr.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/socket.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/socket.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/sockios.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/sockios.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/in.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/siginfo.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/netdb.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/setjmp.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/setjmp.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/signal.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/signum.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sigaction.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sigcontext.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/sigcontext.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sigstack.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/ucontext.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/procfs.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/time.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/user.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/sigthread.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/paths.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/stdio.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_stdio.h \
  /usr/src/output/host/lib/gcc/arm-buildroot-linux-uclibcgnueabihf/6.4.0/include/stdarg.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/stdlib.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/waitflags.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/waitstatus.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/alloca.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/string.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/libgen.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/poll.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/poll.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/poll.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/ioctl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/ioctls.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/ioctls.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/ioctls.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/ioctl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/ioctl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/ioctl.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/ioctl-types.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/ttydefaults.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/mman.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/mman.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/mman-common.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/wait.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/termios.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/termios.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/uClibc_clk_tck.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/param.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/param.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm/param.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/asm-generic/param.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/pwd.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/grp.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/shadow.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/mntent.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/sys/statfs.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/statfs.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/utmpx.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/bits/utmpx.h \
  /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/arpa/inet.h \
  include/xatonum.h \

util-linux/dmesg.o: $(deps_util-linux/dmesg.o)

$(deps_util-linux/dmesg.o):
