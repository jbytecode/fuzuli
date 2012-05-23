#!/bin/bash
cd Interpreter
cd Debug
make clean
cd ..
cd ..


cd Core
cd Debug
make clean
cd ..
cd ..

cd Main
cd Debug
make clean
cd ..
cd ..


sudo rm -Rf /usr/lib/fuzuli/*
