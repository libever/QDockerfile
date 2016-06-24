#!/bin/sh

docker build -t qdocker/base:7 .


echo "/usr/sbin/sshd -D"
