cmd_arch/arm/boot/dts/bcm2709-rpi-2-b.dtb := mkdir -p arch/arm/boot/dts/ ; /usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc -E -Wp,-MD,arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.dts.tmp arch/arm/boot/dts/bcm2709-rpi-2-b.dts ; ./scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/bcm2709-rpi-2-b.dtb -b 0 -iarch/arm/boot/dts/ -i./scripts/dtc/include-prefixes -@ -H epapr -Wno-unit_address_vs_reg -Wno-simple_bus_reg -Wno-unit_address_format -Wno-pci_bridge -Wno-pci_device_bus_num -Wno-pci_device_reg  -d arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.d.dtc.tmp arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.dts.tmp ; cat arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.d.pre.tmp arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.d.dtc.tmp > arch/arm/boot/dts/.bcm2709-rpi-2-b.dtb.d

source_arch/arm/boot/dts/bcm2709-rpi-2-b.dtb := arch/arm/boot/dts/bcm2709-rpi-2-b.dts

deps_arch/arm/boot/dts/bcm2709-rpi-2-b.dtb := \
  arch/arm/boot/dts/bcm2709.dtsi \
  arch/arm/boot/dts/bcm2836.dtsi \
  arch/arm/boot/dts/bcm283x.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/bcm2835.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/bcm2835.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/bcm2835-aux.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  arch/arm/boot/dts/bcm270x.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/power/raspberrypi-power.h \
  arch/arm/boot/dts/bcm2708-rpi.dtsi \
  arch/arm/boot/dts/bcm283x-rpi-smsc9514.dtsi \

arch/arm/boot/dts/bcm2709-rpi-2-b.dtb: $(deps_arch/arm/boot/dts/bcm2709-rpi-2-b.dtb)

$(deps_arch/arm/boot/dts/bcm2709-rpi-2-b.dtb):
