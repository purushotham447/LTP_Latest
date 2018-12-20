#!/bin/ksh
#
# File:		crud.ksh
# Author:	Robin T. Miller
# Date:		December 22nd, 2008
#
# Description:
#	A Korn shell script using the datatest (dt) program to
# simulate the I/O behaviour implemented within the crud program.
#
# Note: The original crud in cluster/fs/crud/linux/crud, is a
# multi-threaded tool. Since dt is not multi-threaded ar present,
# multiple processes are used to closely simulate the crud tool.
# Also, the original crud writes two stripes, truncates the file,
# then writes the last two stripes, and does not verify the data.
# The C crud tool reopen's and continues after errors occur.
#
# RFE's? Allow nodes, threads, and stripe width to be arguments.
#
typeset prog=${0##*/}
typeset DT_PATH=${DT_PATH:-$(whence dt)}
typeset DT_PATH=${DT_PATH:-/usr/software/test/bin/dt.latest}

#
# Local Definitions:
#
typeset NODES=${NODES:-4}
typeset -i THREAD_COUNT=${THREAD_COUNT:-32}
typeset STRIPE_WIDTH=${STRIPE_WIDTH:-64*1024*1024}
(( STRIPE_WIDTH=$STRIPE_WIDTH )) 
typeset -i WRITE_OFFSET=${WRITE_OFFSET:-4096}
typeset -i WRITE_SIZE=${WRITE_SIZE:-8192}

function usage
{
	print "Usage: $prog <filename> [runtime]"
	exit 1
}

#
# Expect Two Arguments:
#
[[ $# -lt 1 ]] && usage
[[ $# -gt 2 ]] && usage

#
# Parse The Arguments: (one required, one optional)
#
typeset FILE=$1
if [ $# -eq 2 ] ; then
    typeset RUNTIME=$2
else
    typeset RUNTIME=300
fi

#
# Show Tool Version:
#
${DT_PATH} version

#
# Execute the Command Line:
#
# Note: Add enable=Debug to see seek/write/read operations!
#
${DT_PATH} of=$FILE 					\
	   bs=${WRITE_SIZE}				\
	   position="${STRIPE_WIDTH}-${WRITE_OFFSET}"	\
	   count=${NODES} 				\
	   step=${STRIPE_WIDTH}				\
	   oflags=trunc					\
	   procs=${THREAD_COUNT}			\
	   runtime=${RUNTIME}				\
	   disable=pstats,verbose			\
	   stats=brief

exit $?
