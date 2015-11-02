#!/bin/sh

gcc -shared -fPIC -o m.so m.c -lmymodule -L ../
gcc -shared -fPIC -o n.so n.c -lmymodule -L ../
