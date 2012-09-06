#!/bin/bash

sudo cp libFuzuliMySql.so /usr/lib/fuzuli/libFuzuliMySql.so
sudo cp -R ../nfl/ /usr/lib/fuzuli/
sudo ldconfig /usr/lib/fuzuli

