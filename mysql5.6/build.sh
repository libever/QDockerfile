#!/bin/sh

if [ -f ./mysql-5.6.21.tar.gz ]
then
docker build -t qdocker/mysql5:7 .
else 
wget 
fi

