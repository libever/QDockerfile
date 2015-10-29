#!/bin/sh


cd /root/
gcc -o demo a.c
./demo

mkdir bin
mv ./chinese_lang.sh /bin


cat >> /etc/vimrc <<EOF
set nu
set tabstop=4
set shiftwidth=4

EOF



