#!/bin/bash

cd Interpreter
cd Release
make
cp libfuzuli.so /usr/lib/fuzuli/
cd ..
cd ..


cd Main
cd Release
make
cp fuzuli /usr/lib/fuzuli/
cd ..
cd ..


