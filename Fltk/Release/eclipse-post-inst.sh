#!/bin/bash

sudo cp libFuzuliFltk.so /usr/lib/fuzuli/libFuzuliFltk.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

