#!/bin/ksh

DIR=`dirname $0` 
HOSTS=`/x/eng/rtp/smokejumper/simlibs/bin/simhosts`
LOCALHOST=`hostname | cut -f 1 -d .`
PWD=`pwd`

#
# Ensure we run on a test host (not production systems).
#
echo $HOSTS, | grep -q $LOCALHOST,
if [ $? -eq 1 ] 
then
	HOSTS=`echo $HOSTS | awk -F , '{print $1}'`
	echo Rehosting $0 to $HOSTS
	ssh $HOSTS "cd $PWD; $0 $*"
	exit 1
fi

MPI_DIR=/x/eng/rtp/smokejumper/simlibs/open-mpi-linux64
export PATH=$MPI_DIR/bin:$PATH
export LD_LIBRARY_PATH=$MPI_DIR/lib:$LD_LIBRARY_PATH

DT=dt.latest
DTPATH=/usr/software/test/bin/dt.latest

MPIRUN="mpirun -mca btl sm,tcp,self --display-map --pernode --show-progress --n 4 --host $HOSTS --path $DTPATH --prefix $MPI_DIR"

$MPIRUN $DT of=/var/tmp/dt.data prefix="%d@%h" bs=64k limit=25m pattern=iot disable=pstats runtime=30s flags=direct oflags=trunc
