#!/bin/sh


if [ -f php-5.4.20.tar.gz ] 
then
docker build -t qdocker/php5:7 .
else
echo "need file : php-5.4.20.tar.gz"
echo "download file : "
wget -t 3 --timeout 180 "http://museum.php.net/php5/php-5.4.20.tar.gz" 
if [ $? -eq 0 ]
then
	sh build.sh
else
	rm php-5.4.20.tar.gz
fi
fi
