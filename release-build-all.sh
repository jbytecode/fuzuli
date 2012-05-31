#!/bin/bash

cd Interpreter/Release
make
cd ..
cd ..
sleep 1

cd Core/Release
make
cd ..
cd ..
sleep 1


cd Main/Release
make
cd ..
cd ..
sleep 1


cd tests
./tester.sh
cd ..

