# Parameters from the top level configure
CC=		/usr/src/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
CFLAGS+=	-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -Os -I/usr/src/output/host/bin/../arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/tirpc  
LDLIBS+=	 -L/usr/src/output/host/bin/../arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/lib -ltirpc  
LDFLAGS+=	
