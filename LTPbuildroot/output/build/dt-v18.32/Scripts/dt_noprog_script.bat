@echo off

REM Location - /x/eng/localtest/arch/win32/SAN/common/bin
REM We get called with these parameters                         #
REM dname op dsize offset position lba errno noprogtime         #
REM Where:                                                      #
REM       $0 Name of the program                                #
REM       $1 dname = The device/file name.                      #
REM       $2 op = open/close/read/write/miscompare/noprog       #
REM       $3 dsize = The device block size.                     #
REM       $4 offset = The current file offset.                  #
REM       $5 position = The failing offset within block.        #
REM       $6 lba = The logical block address (relative for FS). #
REM       $7 errno = The error number on syscall errors.        #
REM       $8 noprogtime = The no progress time                  #
REM       $9 userscript = UserScript to execute                 #
REM                                                             #
REM Capture and display these parameters                        #

set program_name=%0
set dev_name=%1
set operation=%2
set dev_bk_sz=%3
set off_set=%4
set pos=%5
set log_blk=%6
set err_num=%7
set no_prog_time=%8
set userscript=%9

echo ##############################################
echo dt trigger script being called - %program_name%
echo Windows DT: The type of error is %operation%
echo ##############################################
echo The device name is %dev_name%
echo The operation is %operation%
echo The device block size is %dev_bk_sz%
echo The offset, position and lba are %off_set%, %pos%, %log_blk%
echo The errno is %err_num%
echo The no progress time is %no_prog_time%
echo ##############################################"

set dt_io_timeout_rc=1
set time_stamp=date /t
echo ##############################################
echo Local Date/TimeStamp:
date /t
time /t
echo ##############################################

if "%userscript%" EQU "" (
    echo ##############################################
    echo %program_name%: No additional user supplied script was specified
    echo ##############################################
) else (
    echo ##############################################
    echo %program_name%: Running User supplied script: %userscript%
    echo ##############################################
    %userscript%
)

echo ##############################################
echo The return code that %program_name% is sending to dt is %dt_io_timeout_rc%
echo ##############################################

exit %dt_io_timeout_rc%
