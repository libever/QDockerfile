#!/bin/sh

cd /sw/nginx-1.9.3
./configure --prefix=/nginx && make && make install

rm -rf /nginx/conf/nginx.conf
cp /sw/nginx.conf /nginx/conf/nginx.conf
rm -rf /nginx/html

