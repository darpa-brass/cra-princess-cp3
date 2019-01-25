#!/bin/sh
# test-compile.sh - compile a test program
# usage: test-compile.sh baseline arch

WORKDIR=/cp2/toolchain/work
TESTFILE_C=test.c
TESTFILE_S=test.s
TESTFILE_O=test.o
TESTFILE_OUT=test

case "$1" in
    A|Ax|C) ;;
    *)
	echo "$0: Invalid baseline argument $1; expected A, Ax, or C" 1>&2
	exit 1
esac
BASELINE="$1"

ARCH="$2"
# expand special-purpose failure arches
case "$ARCH" in
    broken|nocross)
	# "broken" shouldn't make it this far, but just in case treat
	# it the same as "nocross".
	# for "nocross" pick something where the crosscompiler is
	# definitively not available.
	ARCH=vax
	;;
    *)
	;;
esac

echo "test-compile.sh: arch is $ARCH"
case "$ARCH" in
    alpha)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/alpha/dietlibc
	GNUTARGET=alpha-linux-gnu-
	ARCH=alpha
	;;
    arm)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	LDFLAGS_mopt=armelf_linux_eabi
	LDSO=ld-linux.so.3
	PREFIX_LIBC=
	GNUTARGET=arm-linux-gnueabi-
	ARCH=arm
	#  --eh-frame-hdr
	MORELDFLAGS_Ax="-m armelf_linux_eabi -Bstatic -X --hash-style=gnu --as-needed"
	MORELIBS_C=-lgcc
	;;
    arm64|aarch64|aargh64)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/arm64/musl
	GNUTARGET=aarch64-linux-gnu-
	ARCH=arm64
	;;
    hppa)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/hppa/dietlibc
	GNUTARGET=hppa-linux-gnu-
	ARCH=hppa
	;;
    hppa64)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/nonexistent
	GNUTARGET=hppa64-linux-gnu-
	ARCH=hppa64
	;;
    itanium|ia64)
	GCC_BINDIR=/cp2/cross/ia64/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/ia64/binutils/bin/
	PREFIX_LIBC=/cp2/cross/ia64/dietlibc
	GNUTARGET=ia64-linux-gnu-
	ARCH=ia64
	;;
    m68k)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/m68k/uclibc
	GNUTARGET=m68k-linux-gnu-
	ARCH=m68k
	;;
    microblaze)
	GCC_BINDIR=/cp2/cross/microblaze/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/microblaze/binutils/bin/
	PREFIX_LIBC=/cp2/cross/microblaze/musl
	GNUTARGET=microblaze-linux-gnu-
	ARCH=microblaze
	;;
    mips)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=mips-linux-gnu-
	ARCH=mips
	;;
    mips64)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=mips64-linux-gnu-
	ARCH=mips64
	;;
    mipsel)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=mipsel-linux-gnu-
	ARCH=mipsel
	;;
    mips64el)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=mips64el-linux-gnu-
	ARCH=mips64el
	;;
    nios2)
	GCC_BINDIR=/cp2/cross/nios2/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/nios2/binutils/bin/
	PREFIX_LIBC=/cp2/cross/nios2/uclibc
	GNUTARGET=nios2-linux-gnu-
	ARCH=nios2
	;;
    or1k)
	GCC_BINDIR=/cp2/cross/or1k/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/or1k/binutils/bin/
	PREFIX_LIBC=/cp2/cross/or1k/musl
	GNUTARGET=or1k-linux-gnu-
	ARCH=or1k
	;;
    powerpc)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/powerpc/musl
	GNUTARGET=powerpc-linux-gnu-
	ARCH=powerpc
	;;
    powerpc64)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=powerpc64-linux-gnu-
	ARCH=powerpc64
	;;
    riscv32)
	GCC_BINDIR=/cp2/cross/riscv32/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/riscv32/binutils/bin/
	PREFIX_LIBC=/cp2/cross/riscv32/musl
	GNUTARGET=riscv-linux-gnu-
	ARCH=riscv32
	;;
    riscv64)
	GCC_BINDIR=/cp2/cross/riscv64/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/riscv64/binutils/bin/
	PREFIX_LIBC=/cp2/cross/riscv64/musl
	GNUTARGET=riscv64-linux-gnu-
	ARCH=riscv64
	;;
    s390x)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=s390x-linux-gnu-
	ARCH=s390x
	;;
    sh4)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	PREFIX_LIBC=/cp2/cross/sh4/uclibc
	GNUTARGET=sh4-linux-gnu-
	ARCH=sh4
	;;
    sparc)
	GCC_BINDIR=/cp2/cross/sparc/gcc/bin/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/cp2/cross/sparc/binutils/bin/
	PREFIX_LIBC=/cp2/cross/sparc/dietlibc
	GNUTARGET=sparc-linux-gnu-
	ARCH=sparc
	;;
    sparc64)
	GCC_BINDIR=
	GCC_SUFFIX=-5
	BINUTILS_BINDIR=
	LDFLAGS_mopt=elf64_sparc
	PREFIX_LIBC=
	GNUTARGET=sparc64-linux-gnu-
	ARCH=sparc64
	MORELDFLAGS_Ax="-m elf64_sparc -static -relax"
	;;
    vax)
	GCC_BINDIR=/nonexistent/
	GCC_SUFFIX=
	BINUTILS_BINDIR=/nonexistent/
	PREFIX_LIBC=/nonexistent
	GNUTARGET=vax-linux-gnu-
	ARCH=vax
	;;
    x86|i386)
	GCC_BINDIR=
	GCC_SUFFIX=
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=
	ARCH=x86
	MORECFLAGS_Ax=-m32
	MOREASFLAGS_Ax=-m32
	MORELDFLAGS_Ax=-m32
	MORECFLAGS_C=-m32
	MOREASFLAGS_C=-m32
	MORELDFLAGS_C=-m32
	;;
    x86_64)
	GCC_BINDIR=
	GCC_SUFFIX=
	BINUTILS_BINDIR=
	PREFIX_LIBC=
	GNUTARGET=
	ARCH=x86_64
	;;
    *)
	echo "$0: Unknown architecture $2" 1>&2
	exit 1
esac
ARCH="$2"

GNUTARGETx=$(echo "$GNUTARGET" | sed 's/-$//')

if [ "x$LDSO" = x ]; then
    LDSO=ld-linux.so.2
fi

# shared flags
CFLAGS='-O2 -I../csmithinclude'
ASFLAGS=
LDFLAGS=
LIBS=

# flags for baseline A (native compile)
CFLAGS_A=
ASFLAGS_A=--64
LDFLAGS_A='
    --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu
    --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro
    /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o
    /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o
    -L/usr/lib/gcc/x86_64-linux-gnu/5
    -L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/lib/x86_64-linux-gnu -L/lib
    -L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/lib
'
LIBS_A='
    -lgcc
    --as-needed -lgcc_s --no-as-needed -lc -lgcc
    --as-needed -lgcc_s --no-as-needed
    /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/x86_64-linux-gnu/crtn.o
'

# flags for baseline A* (crosscompile with GNU binutils)
# (may be set per-target below)

# for static linking with uclibc
#LIBCDIR=/usr/${GNUTARGETx}/lib
LIBCDIR=/usr/${ARCH}-linux-uclibc/usr/lib
TOOLLIBDIR=/cp2/toolchain/installed/${ARCH}/lib
GCCDIR=/usr/lib/gcc-cross/${GNUTARGETx}/5

CFLAGS_Ax="
	-fno-stack-protector
	-nostdinc -I$LIBCDIR/../include
	-I$GCCDIR/include -I$GCCDIR/include-fixed
	-I/cp2/software/uclibc/kinclude/$ARCH
"
# this is apparently needed only when working out of an uninstalled
# tree. (!?)
#	-include $LIBCDIR/../include/libc-symbols.h

# Note: the default gcc specs issue -dynamic-linker /lib/ld-linux.so.*
# but this does not work if you want to use qemu to cross-run; the file
# is in /usr/${GNUTARGETx}/lib. So since that's what we're doing, do
# that instead.
# update: we should link statically anyway, so it doesn't matter.

# old, for dynamic linking with glibc
#LDFLAGS_Ax="
#	--sysroot=/ --build-id --eh-frame-hdr
#	-dynamic-linker /usr/${GNUTARGETx}/lib/$LDSO -X --hash-style=gnu
#	--as-needed -m $LDFLAGS_mopt -z relro
#	/usr/${GNUTARGETx}/lib/crt1.o /usr/${GNUTARGETx}/lib/crti.o
#	/usr/lib/gcc-cross/${GNUTARGETx}/5/crtbegin.o
#	-L/usr/lib/gcc-cross/${GNUTARGETx}/5 -L/usr/${GNUTARGETx}/lib
#	-L/lib -L/usr/lib -L/usr/${GNUTARGETx}/lib
#"
#LIBS_Ax="
#	-lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed
#	-lgcc_s --no-as-needed
#	/usr/lib/gcc-cross/${GNUTARGETx}/5/crtend.o
#	/usr/${GNUTARGETx}/lib/crtn.o
#"

# old, for static linking with glibc
#LDFLAGS_Ax="
#	--sysroot=/ --build-id --eh-frame-hdr
#	-dynamic-linker /usr/${GNUTARGETx}/lib/$LDSO -X --hash-style=gnu
#	--as-needed -m $LDFLAGS_mopt -z relro
#	/usr/${GNUTARGETx}/lib/crt1.o /usr/${GNUTARGETx}/lib/crti.o
#	/usr/lib/gcc-cross/${GNUTARGETx}/5/crtbegin.o
#	-L/usr/lib/gcc-cross/${GNUTARGETx}/5 -L/usr/${GNUTARGETx}/lib
#	-L/lib -L/usr/lib -L/usr/${GNUTARGETx}/lib
#"
#LIBS_Ax="
#	-lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed
#	-lgcc_s --no-as-needed
#	/usr/lib/gcc-cross/${GNUTARGETx}/5/crtend.o
#	/usr/${GNUTARGETx}/lib/crtn.o
#"

# current

CRT1=$LIBCDIR/crt1.o
CRTI=$LIBCDIR/crti.o
CRTN=$LIBCDIR/crtn.o
CRTIX=$TOOLLIBDIR/crtix.o
#CRTNX=$TOOLLIBDIR/crtnx.o
CRTBEGIN=$GCCDIR/crtbeginT.o
CRTEND=$GCCDIR/crtend.o


# -z relro
LDFLAGS_Ax="
	--sysroot=/ --build-id $MORELDFLAGS_Ax 
	$CRT1 $CRTI $CRTBEGIN
	-L$GCCDIR -L$LIBCDIR
"
LIBS_Ax="--start-group -lgcc -lgcc_eh -lc --end-group $CRTEND $CRTN"


# flags for challenge (crosscompile with our bintools)
CFLAGS_C="$CFLAGS_Ax"
ASFLAGS_C=
LDFLAGS_C="$MORELDFLAGS_C $CRT1 $CRTI $CRTIX $CRTBEGIN -L$GCCDIR -L$LIBCDIR"
LIBS_C="-lgcc -lc $MORELIBS_C $CRTEND $CRTN"
# -lgcc_eh causes problems and isn't needed, so don't use it

echo "test-compile.sh: configured"

cd $WORKDIR || exit 1

#
# Compile the source file.
#

set -e

if [ $BASELINE = "A" ]; then
    # Native compiler, assembler, and linker.
    echo "gcc $CFLAGS -S $TESTFILE_C -o $TESTFILE_S"
    gcc $CFLAGS $CFLAGS_A -S $TESTFILE_C -o $TESTFILE_S
    echo "as $ASFLAGS $ASFLAGS_A -o $TESTFILE_O $TESTFILE_S"
    as $ASFLAGS $ASFLAGS_A -o $TESTFILE_O $TESTFILE_S
    echo "ld $LDFLAGS $LDFLAGS_A -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_A"
    ld $LDFLAGS $LDFLAGS_A -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_A
elif [ $BASELINE = "Ax" ]; then
    # Cross-compiler, GNU binutils assembler and linker
    echo "${GCC_BINDIR}${GNUTARGET}gcc${GCC_SUFFIX} $CFLAGS_Ax $CFLAGS -S $TESTFILE_C -o $TESTFILE_S"
    ${GCC_BINDIR}${GNUTARGET}gcc${GCC_SUFFIX} $CFLAGS_Ax $CFLAGS -S $TESTFILE_C -o $TESTFILE_S
    echo "${BINUTILS_BINDIR}${GNUTARGET}as $ASFLAGS $ASFLAGS_Ax -o $TESTFILE_O $TESTFILE_S"
    ${BINUTILS_BINDIR}${GNUTARGET}as $ASFLAGS $ASFLAGS_Ax -o $TESTFILE_O $TESTFILE_S
    echo "${BINUTILS_BINDIR}${GNUTARGET}ld $LDFLAGS $LDFLAGS_Ax -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_Ax"
    ${BINUTILS_BINDIR}${GNUTARGET}ld $LDFLAGS $LDFLAGS_Ax -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_Ax
else # $BASELINE = "C"
    # Cross-compiler, our bintools assembler and linker
    echo "${GCC_BINDIR}${GNUTARGET}gcc${GCC_SUFFIX} $CFLAGS_C $CFLAGS -S $TESTFILE_C -o $TESTFILE_S"
    ${GCC_BINDIR}${GNUTARGET}gcc${GCC_SUFFIX} $CFLAGS_C $CFLAGS -S $TESTFILE_C -o $TESTFILE_S
    echo "/cp2/toolchain/installed/$ARCH/bin/as $ASFLAGS $ASFLAGS_C -o $TESTFILE_O $TESTFILE_S"
    /cp2/toolchain/installed/$ARCH/bin/$ARCH-elf-linux-as $ASFLAGS $ASFLAGS_C -o $TESTFILE_O $TESTFILE_S
    echo "/cp2/toolchain/installed/$ARCH/bin/ld $LDFLAGS $LDFLAGS_C -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_C"
    /cp2/toolchain/installed/$ARCH/bin/$ARCH-elf-linux-ld $LDFLAGS $LDFLAGS_C -o $TESTFILE_OUT $TESTFILE_O $LIBS $LIBS_C
fi

exit 0
