#!/bin/sh

if [ -f ./node-v0.10.35.tar.gz ]
then
	docker build -t qdocker/nodejs:7 .
else 
	echo "find file : node-v0.10.35.tar.gz"
fi
