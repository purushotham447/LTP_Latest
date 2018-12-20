#!/bin/ksh -p
DT_PATH="dt.latest"
${DT_PATH} version
${DT_PATH}								\
  of=/var/tmp/dt.data bs=random limit=1g pattern=iot prefix="%d@%h"	\
  disable=pstats,verbose stats=brief keepalivet=10			\
  keepalive="count = %C; e = %e; t = %S; IOpS = %IOPS; SpIO = %SPIO"	\
  tkeepalive="STAT +RawMbytes %MBPS +RawReads %R +RawWrites %W"
