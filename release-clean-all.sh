#!/bin/bash
cd Interpreter
cd Release
make clean
cd ..
cd ..


cd Core
cd Release
make clean
cd ..
cd ..

cd Main
cd Release
make clean
cd ..
cd ..


sudo rm -Rf /usr/lib/fuzuli/*
