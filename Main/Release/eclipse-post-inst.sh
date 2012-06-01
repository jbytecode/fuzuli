#!/bin/bash


cp fuzuli /usr/lib/fuzuli/fuzuli
ldconfig /usr/lib/fuzuli
cd ..
cd ..
cd tests
./tester.sh


