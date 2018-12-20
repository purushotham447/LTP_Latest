#!/usr/bin/ksh
########################################################
#
# AUTHOR:     John Diana < John.Diana@netapp.com>
# CO-AUTHOR:  Jody Haynes < Jody.Haynes@netapp.com >
#
# PURPOSE:    To output the I/O Resume Times produced by dt or iomon 
#             over a certain threashold. Always displays MAX and AVG
#
########################################################
noDetail=0
Group_MAX=0
timestamp ()
{
        cmd=$1
        print "=====> $(date '+%A %d%b%Y %I:%M:%S %p') <=====\n"
        print "=====> ${cmd}\n"
}

usage()
{
    script_name=$(basename $0)
        timestamp "${script_name} - a script to gather the I/O Resume Times from a NATE automation run"
        print "Examples:"  
        print "${script_name} -i 60 -l /x/eng/rtpeng-testbeds/san_interop_aix/jhaynes/logs/latest/03_vm_io/IO-fs"
        print "From a top level log directory:"
        print "bash-2.05b$ pwd"
        print "/x/eng/rtpeng-testbeds/san_interop_aix/jhaynes/logs/latest"
        print "${script_name} -i 60      - will show dt and iomon (in Data Collection directories) "No progress" messages above 60 seconds"
        print "Usage: ${script_name} [ -i <Interval in Seconds> ] [ -l <Path to the NATE automation logs>] [-s <Summary only no detail>]"
        print "  -i   I/O Resume Threshold Limit.  Default:  120"
        print "  -l   Location to the NATE automation logs.  Default:  Current Working Directory "
        print "  -s   Supress priniting each no progress message just print summary information Default= print details"
        print "  -g   Show max group line"
        print

        exit 1
}

while getopts "i:l:gsh" arg
do
        case $arg in
        l)  if [ ! -z "${OPTARG}" ]
                then
                        testbed_loc=${OPTARG}
                fi
                ;;
        i)  if [ ! -z "${OPTARG}" ]
                then
                        interval=${OPTARG}
                fi
                ;;
        s)  noDetail=1
                ;;
        g)  Group_MAX=1
                ;;
            h|*)
        usage
                ;;
        esac
done
interval=${interval:-120}
    testbed_def_loc=${testbed_loc:-$(pwd)}
    if [ -d "${testbed_def_loc}" ]
    then
        if [ "${testbed_def_loc}" == "." ]
        then
            testbed_def_loc=$(pwd)
        fi
        print "\n------------------------------------------------------------------"
    
        if [ "${testbed_def_loc}" != "/" ] 
        then
            timestamp "Using the following Log Location:  ${testbed_def_loc}"
        else
            timestamp "You're trying to run this from the root for the root file system '/'"
            exit 1
        fi
    else
        timestamp "OOOps .... I cannot find this location:  ${testbed_def_loc}"
        exit 1
    fi
    print "\b-------------------------------------------------------------------\n"
    for dir in $(find ${testbed_def_loc} -name "*-client*" -type d)
    do
        print ${dir}
        base_dir=$(basename ${dir})
        #test_client=$(echo ${base_dir} | cut -f-2 -d-)
        test_client=$(echo ${base_dir} | sed 's/-client//' )
        timestamp "Looking for I/O resume times greater than ${interval} seconds for this test client:  ${test_client}"
    ####################################################################################################################
    # Find first occurance of Version: print the next field as the dt version                                          #
    # Figure out where the number of seconds column is by looking for the word "seconds!" then use the column previous #
    # Search for other columns to use when displaying the line                                                         #
    # get min and max and record also whenever the value read is less than max1 add it to max2 since the value resets  #
    # when io resumes (will be smaller than max1) Count how many times this occurs. For the AVG divide MAX2 by COUNT1  #
    # if count1 is not greater than 0 then do not print or do the calculation for AVG so as to prevent div by zero     #
    # Record and display if desired the maximum for groups or no progs                                                 #
    ####################################################################################################################
          awk '{for (i=1;i<=NF;i++) if ($i ~ /Version:/) {print "DT_Version: "substr($(i+1),1,index($(i+1),",")-1);exit}}' ${dir}/*.*log
#          grep -i "no progress made " ${dir}/*.*log | gawk --re-interval '
          awk  '/No progress made/{
             for (i=1;i<=NF;i++) 
			 
                if ($i ~ /seconds!/) {sec_field=(i-1)}   
                else if ($i ~ /(record)/) {record_line=i;record_no=i+1}
                else if ($i ~ /(\(\))/) {function_line=i}
	     if ($sec_field > '"${interval}"' )
             {           
			  present_max=$sec_field
 			  if (present_max < past_max)
               { 
			    past_max=0
			    if ('"${Group_MAX}"' != 0) {print past_max_line}
			   }
			  else 
			   {
			    past_max=present_max
			    past_max_line="**************************\nMAX Line For Group - Client '"${test_client}"' in '"${dir}"': \n"substr($1,index($1,":")+1,8)" "$2" Function: "$function_line" No progress for: "$sec_field" seconds\n**************************"
			   }
               if ('"${noDetail}"' !=1) {print substr($1,index($1,":")+1,8)" "$2" Function: "$function_line" No progress for: "$sec_field" seconds"}
			 } 
           if (min1 > $sec_field) { min1 = $sec_field}
           if (max1 > $sec_field) { max2+=max1;count1+=1}
           if (max1 < $sec_field) { max1=$sec_field}
           count+=1;total+=$sec_field
	     } 
         END { 
                if ('"${Group_MAX}"' != 0){print past_max_line}
         	printf "   I/O Resume Times for %-20s:","'"$test_client"'";
         	if (max1 <= 0) printf "No IO Resume times found in this log!"
         	if (max1>0)printf "MAX=%-6d",max1
         	if (count1>0) printf " AVG=%d",max2/count1
         	printf"\n------------------------------------------------------------------\n" 
             }' ${dir}/*.*log
    done

