#!/bin/sh

gcc -c m.c
gcc -c n.c
gcc -shared -fPIC -o m.so m.o ../react.o ../net.o
gcc -shared -fPIC -o n.so n.o ../react.o ../net.o
