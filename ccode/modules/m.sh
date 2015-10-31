#!/bin/sh

gcc -c m1.c	
gcc -c m2.c	
gcc -shared -fPIC -o m1.so m1.o
gcc -shared -fPIC -o m2.so m2.o

#so文件辅助上dlopen和dlsym
