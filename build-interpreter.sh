#!/bin/bash

cd Interpreter
cd Debug
sudo make
sudo cp libfuzuli.so /usr/lib/fuzuli/
cd ..
cd ..


cd Main
cd Debug
sudo make
sudo cp fuzuli /usr/lib/fuzuli/
cd ..
cd ..


