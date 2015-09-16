#!/bin/sh

cd /sw/go/src
./all.bash

echo "PATH=\$PATH:/sw/go/bin/" >> /etc/bashrc
