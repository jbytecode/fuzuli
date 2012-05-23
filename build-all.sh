#!/bin/bash

./build-interpreter.sh
sleep 1

./build-libs.sh
sleep 1

cd tests
./tester.sh
cd ..

