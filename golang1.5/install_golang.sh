#!/bin/sh

mv /sw/golang15/go-go1.5.4 /sw/golang15/go
mkdir -p /gocode

cd /sw/golang15/go/src
./all.bash

echo ""
