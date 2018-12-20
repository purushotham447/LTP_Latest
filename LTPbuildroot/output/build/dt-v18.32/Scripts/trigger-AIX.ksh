#!/usr/bin/ksh -p
# /x/eng/locals/powerpc-ibm-aix5.1/test/bin                   #
# We get called with these parameters                         #
# dname op dsize offset position lba errno noprogtime         #
# Where:                                                      #
#       $1 dname = The device/file name.                      #
#       $2 op = open/close/read/write/miscompare/noprog       #
#       $3 dsize = The device block size.                     #
#       $4 offset = The current file offset.                  #
#       $5 position = The failing offset within block.        #
#       $6 lba = The logical block address (relative for FS). #
#       $7 errno = The error number on syscall errors.        #
#       $8 noprogtime = The no progress time                  #
#                                                             #
# Capture and display these parameters                        #
my_name="dt_io_timeout.ksh"
dev_name=$1
operation=$2
dev_bk_sz=$3
off_set=$4
pos=$5
log_blk=$6
err_num=$7
no_prog_time=$8

ActionItem=$9

echo "$my_name *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
echo "The device name is $dev_name."
echo "The operation is $operation."
echo "The device block size is $dev_bk_sz." 
echo "The offset, position and lba are $off_set, $pos, $log_blk."
echo "The errno is $err_num."
echo "The no progress time is $no_prog_time."           
echo "$my_name *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"

if [[ $operation = "noprog" ]]; then
# return code meanings                                 #
# CONTINUE = 0, TERMINATE = 1, SLEEP = 2, or ABORT = 3 #
        dt_io_timeout_rc=3
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "TimeStamp: $(date '+%A %d%b%Y %I:%M:%S %p')"
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"   
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "$my_name: I/O has exceeded the limit."
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        # Now run something useful to display information - like host_info #
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "$my_name: Running host_info"
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        
        if [ -z "${ActionItem}" ]
        then
                /x/eng/locals/powerpc-ibm-aix5.1/test/bin/host_info
        else
                ${ActionItem}
        fi
elif [[ ${err_num} -gt 0 ]]; then 
        dt_io_timeout_rc=3
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "TimeStamp: $(date '+%A %d%b%Y %I:%M:%S %p')"
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"   
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "$my_name: An error ${err_num} has occurred ."
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        echo "$my_name: Running ${ActionItem}"
        echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
        ${ActionItem}
else
   dt_io_timeout_rc=0
fi
echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"
echo "The return code that $my_name is sending to dt is $dt_io_timeout_rc."
echo "*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"

# Set the return code and exit #
exit $dt_io_timeout_rc
