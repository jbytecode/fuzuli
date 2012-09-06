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

cd Fltk/Release
make
cd ..
cd ..
sleep 1

cd GD/Release
make
cd ..
cd ..
sleep 1

cd Java/Release
make
cd ..
cd ..
sleep 1


cd MySql/Release
make
cd ..
cd ..

cd NCurses/Release
make 
cd ..
cd ..

cd Socket/Release
make
cd ..
cd ..

cd Thread/Release
make
cd ..
cd ..

#cd tests
#./tester.sh
#cd ..

