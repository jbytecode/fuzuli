#!/bin/bash

cd Interpreter
cd Release
sudo make
sudo cp libfuzuli.so /usr/lib/fuzuli/
cd ..
cd ..


cd Main
cd Release
sudo make
sudo cp fuzuli /usr/lib/fuzuli/
cd ..
cd ..


