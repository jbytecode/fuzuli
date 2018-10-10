#!/bin/bash

sudo cp libFuzuliNCurses.so /usr/lib/fuzuli/libFuzuliNCurses.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

