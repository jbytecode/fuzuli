#!/bin/bash
rm test.o run runtime.o
fuzuli --serialize s.fzl > test.asm
as -c test.asm -o test.o
cc -c runtime/runtime.c -o runtime.o
cc test.o runtime.o -o run
./run


