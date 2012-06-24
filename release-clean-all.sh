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

cd Fltk
cd Release
make clean
cd ..
cd ..


cd GD
cd Release
make clean
cd ..
cd ..

cd Java
cd Release
make clean
cd ..
cd ..

cd MySql
cd Release
make clean
cd ..
cd ..

cd NCurses
cd Release
make clean
cd ..
cd ..

cd Socket
cd Release
make clean
cd ..
cd ..


rm -Rf /usr/lib/fuzuli/*

