#!/bin/bash
#******************************************************************************
#
# Bash-Script to create Plustek-Scannerdriver modules for Kernel 2.4, 2.6 and 3.x
# out of the backend sources...
#

BUILD_DIR=$PWD/build
SRC_DIR=$PWD/../../backend
MAKEFILE=$PWD/Makefile.kernel26
KERNEL_V=`uname -r`
OSMINOR=`uname -r | cut -b 3`
OSMAJOR=`uname -r | cut -b 1`

#
# some intro ;-)
#
echo "This script will try and build a suitable kernel-module for your system."
echo "If you'd like to make the module WITH debug output, restart this script"
echo "with as follows:"
echo "./MakeModule.sh DEBUG=y"
echo "Press <ENTER> to continue or <CTRL><C> to cancel."
read

#
# we need to be root user...
#
echo -n "Check for root..."
if [ $EUID -ne 0 ]; then
	echo -e "\b\b\b - failed"
	echo "Please retry as root user."
	exit -1
fi
echo -e "\b\b\b - done."

#
# Version checks...
#
echo -e "\nCheck for kernelversion:"
if [ "$OSMAJOR" == "3" ];then
	echo "Using makefile for kernel 2.6.x - okay for kernel 3 as well..."
	MAKEFILE=$PWD/Makefile.kernel26
elif [ "$OSMINOR" == "6" ]; then
	echo "Using makefile for kernel 2.6.x"
	MAKEFILE=$PWD/Makefile.kernel26
elif [ "$OSMINOR" == "4" ]; then
	echo "Using makefile for kernel 2.4.x"
	MAKEFILE=$PWD/Makefile.kernel24
else
	echo "Your kernelversion >"$OSMAJOR"."$OSMINOR"< is probably not supported"
	exit -2
fi

#
# Setup...
#
echo -e "Build-directory: \n"$BUILD_DIR
echo -n "Removing build-directory..."
rm -rf $BUILD_DIR
echo -e "\b\b\b - done."

echo -n "Creating build-directory..."
mkdir $BUILD_DIR
cd $BUILD_DIR
echo -e "\b\b\b - done.\n"

echo -n "Linking source files..."
C_FILES=`ls $SRC_DIR/plustek-pp_*.c`
H_FILES=`ls $SRC_DIR/plustek-pp_*.h`

for F in $C_FILES $H_FILES $SRC_DIR/plustek-pp.h $SRC_DIR/plustek_pp.c; do
	ln -s $F .
done
echo -e "\b\b\b - done."

echo -n "Copying Makefile to build-directory..."
cp $MAKEFILE Makefile
echo -e "\b\b\b - done."

#
# Building the module...
#
echo "Making the module..."
if [ "$OSMAJOR" == "2" -a "$OSMINOR" == "4" ]; then
	make all $1
else
	make -C /lib/modules/$KERNEL_V/build/ SUBDIRS=$BUILD_DIR modules $1
fi
RES=$?
cd ..
if [ $RES != 0 ]; then
	echo "There were some build errors..."
	exit -1
fi
echo "done."

echo "Should I install the module?"
echo "Press <ENTER> to continue or <CTRL><C> to cancel."
read

make -C $BUILD_DIR install

echo "Should I try and load the module?"
echo "If this step fails, check the kernel-log."
echo "Press <ENTER> to continue or <CTRL><C> to cancel."
read

make -C $BUILD_DIR load
echo "done."

echo "Should I remove the build directory?"
echo "Press <ENTER> to continue or <CTRL><C> to cancel."
read

rm -rf $BUILD_DIR
echo "done."
