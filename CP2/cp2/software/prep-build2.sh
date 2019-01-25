#!/bin/sh
# prep-build2.sh - build moreadditional software
#
# This script arranges the following:
#    - uClibc-ng
#
# It is separate from prep-build to get more docker caching; I got quite
# tired of watching Rosette build while debugging the libc build.
#

echo "cd /cp2/software/uclibc"
cd /cp2/software/uclibc || exit 1

echo "mkdir kinclude kinclude/arm kinclude/sparc64"
mkdir kinclude kinclude/arm kinclude/sparc64 || exit 1
for D in asm asm-generic linux; do
   echo "ln -s /usr/sparc64-linux-gnu/include/$D kinclude/sparc64/$D"
   ln -s /usr/sparc64-linux-gnu/include/$D kinclude/sparc64/$D || exit 1
   echo "ln -s /usr/arm-linux-gnueabi/include/$D kinclude/arm/$D"
   ln -s /usr/arm-linux-gnueabi/include/$D kinclude/arm/$D || exit 1
done

echo "ln -s /usr/bin/arm-linux-gnueabi-gcc-5 /usr/local/bin/arm-linux-gnueabi-gcc"
ln -s /usr/bin/arm-linux-gnueabi-gcc-5 /usr/local/bin/arm-linux-gnueabi-gcc
echo "ln -s /usr/bin/sparc64-linux-gnu-gcc-5 /usr/local/bin/sparc64-linux-gnu-gcc"
ln -s /usr/bin/sparc64-linux-gnu-gcc-5 /usr/local/bin/sparc64-linux-gnu-gcc

echo "cd /cp2/software/uclibc/uclibc"
cd /cp2/software/uclibc/uclibc || exit 1
echo "cp ../../uclibc-config-sparc64 .config"
cp ../../uclibc-config-sparc64 .config || exit 1
echo "make oldconfig"
make oldconfig || exit 1
echo "make CROSS_COMPILE=sparc64-linux-gnu-"
make CROSS_COMPILE=sparc64-linux-gnu- || exit 1
echo "CROSS_COMPILE=sparc64-linux-gnu-make install"
make CROSS_COMPILE=sparc64-linux-gnu- install || exit 1
echo "make clean"
make clean || exit 1
echo "../../uclibc-config-arm .config"
cp ../../uclibc-config-arm .config || exit 1
echo "make oldconfig"
make oldconfig || exit 1
echo "make CROSS_COMPILE=arm-linux-gnueabi-"
make CROSS_COMPILE=arm-linux-gnueabi- || exit 1
echo "make CROSS_COMPILE=arm-linux-gnueabi- install"
make CROSS_COMPILE=arm-linux-gnueabi- install || exit 1

exit 0
