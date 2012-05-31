#!/bin/bash

cd ..
cd ..

cd Interpreter
cd Release
cp libfuzuli.so /usr/lib/fuzuli/
cd ..
cd ..


cd Main
cd Release
cp fuzuli /usr/lib/fuzuli/
cd ..
cd ..

cd Core
cp -R nfl /usr/lib/fuzuli/
cd Release
cp *.so /usr/lib/fuzuli/
cd ..
cd ..

