#!/bin/sh


cd /root/
gcc -o demo a.c
./demo

mkdir bin
mv ./chinese_lang.sh /bin

