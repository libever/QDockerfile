#!/bin/sh

cd /sw/node-v0.10.35
./configure --prefix=/nodejs && make && make install


echo "PATH=\$PATH:/nodejs/bin/" >> /etc/bashrc
