#!/bin/sh

cd /sw/nginx-1.9.3
./configure --prefix=/nginx && make && make install

