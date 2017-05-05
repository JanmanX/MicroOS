#!/bin/bash

# Print all output
set -x
mkdir $HOME/src
export NJOBS=4

export PREFIX="$HOME/opt/cross"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

export GCC=gcc-6.3.0
export BINUTILS=binutils-2.28

# BINUTILS
cd $HOME/src
wget http://ftp.gnu.org/gnu/binutils/${BINUTILS}.tar.bz2
tar xf ${BINUTILS}.tar.bz2

mkdir build-binutils
cd build-binutils
../${BINUTILS}/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make all -j$(NJOBS)
make install

# GCC
cd $HOME/src

wget ftp://ftp.mpi-sb.mpg.de/pub/gnu/mirror/gcc.gnu.org/pub/gcc/releases/${GCC}/${GCC}.tar.bz2
tar xf ${GCC}.tar.bz2

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH

cd ${GCC}
contrib/download_prerequisites
cd ..

mkdir build-gcc
cd build-gcc
../${GCC}/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(NJOBS)
make all-target-libgcc -j$(NJOBS)
make install-gcc
make install-target-libgcc


# Messsage for user
echo 'Add to path: PATH="$HOME/opt/cross/bin:$PATH"'
