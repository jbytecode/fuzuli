#!/bin/bash

cd Core
cd Release
make clean
make
cd ..
cd ..

cp Core/Release/libFuzuliCore.so /usr/lib/fuzuli/
cp -R Core/nfl /usr/lib/fuzuli/
ldconfig /usr/lib/fuzuli
fuzuli samples/program.fzl


