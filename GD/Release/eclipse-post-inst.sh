#!/bin/bash

sudo cp libFuzuliGd.so /usr/lib/fuzuli/libFuzuliGd.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

