cmd_arch/arm/boot/zImage := /usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-objcopy -O binary -R .comment -S  arch/arm/boot/compressed/vmlinux arch/arm/boot/zImage
