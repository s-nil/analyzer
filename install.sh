#!/bin/bash

VERSION="9.0.0"

URL="http://releases.llvm.org"

WGET=wget
DOWNLOADDIR=$HOME
SUFIX="tar.xz"
LLVM_SRC="llvm-$VERSION.src"
LLVM_URL=$URL/$VERSION/$LLVM_SRC.$SUFIX
CLANG_SRC="cfe-$VERSION.src"
CLANG_URL=$URL/$VERSION/$CLANG_SRC.$SUFIX

llvm-config --version > /dev/null
r=$?
if [ $r == 0 ]; then
    echo "yes"
else
    $WGET -O $DOWNLOADDIR/$LLVM_SRC.$SUFIX $LLVM_URL
    tar xf $DOWNLOADDIR/$LLVM_SRC.$SUFIX -C $DOWNLOADDIR
    rm $DOWNLOADDIR/$LLVM_SRC.$SUFIX
    mv $DOWNLOADDIR/$LLVM_SRC $DOWNLOADDIR/llvm-$VERSION
    LLVM_SRC="llvm-$VERSION"
fi


clang --version > /dev/null
r=$?
if [ $r == 0 ]; then
    echo "yes"
else
    $WGET -O $DOWNLOADDIR/$CLANG_SRC.$SUFIX $CLANG_URL
    tar xf $DOWNLOADDIR/$CLANG_SRC.$SUFIX -C $DOWNLOADDIR
    rm $DOWNLOADDIR/$CLANG_SRC.$SUFIX
    mv $DOWNLOADDIR/$CLANG_SRC $DOWNLOADDIR/cfe-$VERSION
    CLANG_SRC="cfe-$VERSION"
    mv $DOWNLOADDIR/$CLANG_SRC $DOWNLOADDIR/$LLVM_SRC/tools/clang
fi

cd $DOWNLOADDIR/$LLVM_SRC 
pwd
mkdir build
cd build

cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DLLVM_TARGETS_TO_BUILD="X86"
make -j2
