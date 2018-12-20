#!/bin/sh
set -e
chown -h -R 0:0 /usr/src/output/target
/usr/src/output/host/bin/makedevs -d /usr/src/output/build/buildroot-fs/device_table.txt /usr/src/output/target
   	rm -f /usr/src/output/images/rootfs.ext2
	/usr/src/output/host/sbin/mkfs.ext4 -d /usr/src/output/target -r 1 -N 0 -m 5 -L "" -O ^64bit /usr/src/output/images/rootfs.ext2 "400M" || { ret=$?; echo "*** Maybe you need to increase the filesystem size (BR2_TARGET_ROOTFS_EXT2_SIZE)" 1>&2; exit $ret; }
