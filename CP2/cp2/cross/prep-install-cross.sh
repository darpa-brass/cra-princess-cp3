#!/bin/sh
# install-toolchains.sh: install toolchains in docker image
# usage: install-toolchains.sh arches
#
# currently understood arches:
#
#     alpha arm arm64/aarch64 hppa hppa64 itanium m68k microblaze mips
#     mips64 mipsel mips64el or1k powerpc powerpc64 riscv32 riscv64
#     s390x sh4 sparc sparc64 vax x86/i386 x86_64
#
# but not all of these are supported. Recommended arches currently seem to be:
#     arm mips powerpc64 s390x(!) sparc64 x86 x86_64
#
# Note that this knows about a lot of arches not because we're
# intending to support all of them for phase2 but because having them
# known here doesn't cost much and it provides flexibility for
# choosing what we do support for phase2.
#

FAIL=0

############################################################
# compile binutils

build_binutils() {
    echo "Architecture $ARCH requires compiling binutils" 1>&2
    echo "This is not yet supported" 1>&2
    FAIL=1
}

############################################################
# compile gcc

build_gcc() {
    case "$1" in
	5) GCCVER=5.5.0;;
	6) GCCVER=6.4.0;;
	7) GCCVER=7.3.0;;
	*) echo "Unknown gcc release $1" 1>&2; FAIL=1; return;;
    esac
    
    echo "Architecture $ARCH requires compiling gcc $GCCVER" 1>&2
    echo "This is not yet supported" 1>&2
    FAIL=1
}

############################################################
# compile libc

musl_libc() {
    echo "Architecture $ARCH requires compiling musl libc" 1>&2
    echo "This is not yet supported" 1>&2
    FAIL=1
}

uclibc() {
    echo "Architecture $ARCH requires compiling uclibc" 1>&2
    echo "This is not yet supported" 1>&2
    FAIL=1
}

dietlibc() {
    echo "Architecture $ARCH requires compiling dietlibc" 1>&2
    echo "This is not yet supported" 1>&2
    FAIL=1
}

nolibc() {
    echo "Architecture $ARCH has no known supported C library" 1>&2
    FAIL=1
}

############################################################
# binary installs

fromapt() {
    echo "apt-get install $@"
    apt-get -y install "$@" || exit 1
}

############################################################
# dispatch

for arch in "$@"; do
    ARCH="$arch"
    case "$arch" in
	alpha)
	    fromapt binutils alpha-linux-gnu
	    fromapt gcc-5-alpha-linux-gnu
	    dietlibc
	    ;;
	arm)
	    # Use the softfloat version as it's more likely to work with
	    # an emulator.
	    # Note: It is pitch dark. You are likely to be eaten by a gnue.
	    fromapt binutils-arm-linux-gnueabi=2.26.1-1ubuntu1~16.04.6
	    fromapt gcc-5-arm-linux-gnueabi=5.4.0-6ubuntu1~16.04.9cross1
	    fromapt gcc-5-multilib=5.4.0-6ubuntu1~16.04.10
	    fromapt gcc-5-multilib-arm-linux-gnueabi=5.4.0-6ubuntu1~16.04.9cross1
	    #fromapt binutils-arm-linux-gnueabihf
	    #fromapt gcc-5-arm-linux-gnueabihf
	    #fromapt gcc-5-multilib-arm-linux-gnueabihf
	    ;;
	arm64|aarch64|aargh64)
	    fromapt binutils-aarch64-linux-gnu
	    fromapt gcc-5-aarch64-linux-gnu
	    musl_libc
	    ;;
	hppa)
	    fromapt binutils-hppa-linux-gnu
	    fromapt gcc-5-hppa-linux-gnu
	    dietlibc
	    ;;
	hppa64)
	    fromapt binutils-hppa64-linux-gnu
	    fromapt gcc-5-hppa64-linux-gnu
	    nolibc
	    ;;
	itanium|ia64)
	    build_binutils
	    build_gcc 5
	    dietlibc
	    ;;
	m68k)
	    fromapt binutils-m68k-linux-gnu
	    fromapt gcc-5-m68k-linux-gnu
	    uclibc
	    ;;
	microblaze)
	    build_binutils
	    build_gcc 5
	    musl_libc
	    ;;
	mips)
	    fromapt binutils-mips-linux-gnu
	    fromapt gcc-5-mips-linux-gnu
	    fromapt gcc-5-multilib-mips-linux-gnu
	    ;;
	mips64)
	    fromapt binutils-mips64-linux-gnu
	    fromapt gcc-5-mips64-linux-gnu
	    fromapt gcc-5-multilib-mips64-linux-gnu
	    ;;
	mipsel)
	    fromapt binutils-mipsel-linux-gnu
	    fromapt gcc-5-mipsel-linux-gnu
	    fromapt gcc-5-multilib-mipsel-linux-gnu
	    ;;
	mips64el)
	    fromapt binutils-mips64el-linux-gnu
	    fromapt gcc-5-mips64el-linux-gnu
	    fromapt gcc-5-multilib-mips64el-linux-gnu
	    ;;
	nios2)
	    build_binutils
	    build_gcc 5
	    uclibc
	    ;;
	or1k)
	    build_binutils
	    build_gcc 5
	    musl_libc
	    ;;
	powerpc)
	    # There's also gnuspe; not sure what it is or whether we want it
	    fromapt binutils-powerpc-linux-gnu
	    fromapt gcc-5-powerpc-linux-gnu
	    musl_libc
	    ;;
	powerpc64)
	    fromapt binutils-powerpc64-linux-gnu
	    fromapt gcc-5-powerpc64-linux-gnu
	    fromapt gcc-5-multilib gcc-5-multilib-powerpc64-linux-gnu
	    ;;
	riscv32)
	    build_binutils
	    build_gcc 7
	    nolibc
	    ;;
	riscv64)
	    build_binutils
	    build_gcc 7
	    nolibc
	    ;;
	s390x)
	    fromapt binutils-s390x-linux-gnu
	    fromapt gcc-5-s390x-linux-gnu
	    fromapt gcc-5-multilib gcc-5-multilib-s390x-linux-gnu
	    ;;
	sh4)
	    fromapt binutils-sh4-linux-gnu
	    fromapt gcc-5-sh4-linux-gnu
	    uclibc
	    ;;
	sparc)
	    # XXX binutils
	    # XXX compiler
	    dietlibc
	    ;;
	sparc64)
	    fromapt binutils-sparc64-linux-gnu=2.26.1-1ubuntu1~16.04.6
	    fromapt gcc-5-sparc64-linux-gnu=5.4.0-6ubuntu1~16.04.9cross1
	    fromapt gcc-5-multilib=5.4.0-6ubuntu1~16.04.10
	    fromapt gcc-5-multilib-sparc64-linux-gnu=5.4.0-6ubuntu1~16.04.9cross1
	    ;;
	vax)
	    # XXX binutils
	    # XXX compiler
	    # XXX libc
	    ;;
	x86|i386)
	    # we'll just use the native binutils
	    # we'll just use the native compiler
	    fromapt gcc-5-multilib # get the 32-bit libc
	    ;;
	x86_64)
	    # we'll just use the native binutils
	    # we'll just use the native compiler
	    # we'll just use the native libc
	    ;;
	*)
	    echo "Unknown architecture $arch" 1>&2
	    FAIL=1
	    ;;
    esac
done
	     
exit $FAIL
