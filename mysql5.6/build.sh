#!/bin/sh

if [ -f ./mysql-5.6.21.tar.gz ]
then
	docker build -t qdocker/mysql56:7 .
else 
	echo "find file : mysql-5.6.21.tar.gz"
fi
