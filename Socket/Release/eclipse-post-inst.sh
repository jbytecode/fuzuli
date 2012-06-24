#!/bin/bash

sudo cp libFuzuliSocket.so /usr/lib/fuzuli/libFuzuliSocket.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

