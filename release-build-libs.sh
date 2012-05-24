#!/bin/bash

cd Core
cd Release
make clean
sudo make
cd ..
cd ..

sudo cp Core/Release/libFuzuliCore.so /usr/lib/fuzuli/
sudo cp -R Core/nfl /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli
fuzuli samples/program.fzl


