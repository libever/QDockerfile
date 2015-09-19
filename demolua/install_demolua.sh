#!/bin/sh

cd /sw/lua-5.3.1
sed -i "s/INSTALL_TOP=\ \/usr\/local/INSTALL_TOP=\/lua/g" Makefile 
make linux
make install
