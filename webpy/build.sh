#!/bin/sh

file_name="web.py-0.33.tar.gz"
file_url="http://webpy.org/static/web.py-0.33.tar.gz"

if [ -f $file_name ] 
then
docker build -t qdocker/webpy:7 .
else
echo "need file : $file_name"
echo "download file : "
wget -t 3 --timeout 180 $file_url
if [ $? -eq 0 ]
then
	sh build.sh
else
	rm $file_name
	echo "################"
	echo "$file_name get error ... try to change other version of webpy ."
fi
fi

