#!/bin/bash

sudo cp libFuzuliJava.so /usr/lib/fuzuli/libFuzuliJava.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

