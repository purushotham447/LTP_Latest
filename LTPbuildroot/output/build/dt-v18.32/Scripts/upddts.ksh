#!/bin/ksh
# Update the source files.
cp -p dt.h dt*.c ../dt.d/
# Rebuild this on your Windows notebook.
cp -p cygnus/dt.exe ../dt.d/cygnus/
cp -p windows/Debug/dt.exe ../dt.d/windows/Debug/
cp -p windows/Release/dt.exe ../dt.d/windows/Release/
