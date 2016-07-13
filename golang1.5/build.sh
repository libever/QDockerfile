#!/bin/sh

echo "This version is golang1.5 "
echo "ENTER TO CONTINUE ..."
read m
if [ -f ./go1.5.3.linux-amd64.tar.gz ]
then
	docker build -t qdocker/golang15:7 .
else 
	echo "can't find file : go1.5.3.linux-amd64.tar.gz"
	echo "download...."
	wget -t 3 --timeout 180 "http://www.golangtc.com/static/go/go1.5.3/go1.5.3.linux-amd64.tar.gz"
	if [ $? -eq 0 ]
	then
		sh build.sh
	else
		rm go1.5.3.linux-amd64.tar.gz
		echo "################"
		echo "go1.5.3.linux-amd64.tar.gz get error ... try to change other version of golang ."
	fi

fi


