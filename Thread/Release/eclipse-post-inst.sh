#!/bin/bash

sudo cp libFuzuliThread.so /usr/lib/fuzuli/libFuzuliThread.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

