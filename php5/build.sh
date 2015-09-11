#!/bin/sh


if [ -f php-5.4.20.tar.gz ] 
then
docker build -t qdocker/php5:7 .
else
echo "need file : php-5.4.20.tar.gz"
fi
