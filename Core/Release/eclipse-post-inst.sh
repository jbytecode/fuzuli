#!/bin/bash

sudo cp libFuzuliCore.so /usr/lib/fuzuli/libFuzuliCore.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

