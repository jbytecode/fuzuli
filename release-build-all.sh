#!/bin/bash

./release-build-interpreter.sh
sleep 1

./release-build-libs.sh
sleep 1

cd tests
./tester.sh
cd ..

