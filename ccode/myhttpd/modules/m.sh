#!/bin/sh

gcc -c m.c	
gcc -shared -fPIC -o libtest.so *.o

#so文件辅助上dlopen和dlsym
