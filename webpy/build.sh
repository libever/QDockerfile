#!/bin/sh

function check_file() {
	file_name=$1
	file_url=$2
	if [ -f ./packages/$file_name ] 
	then
		echo "chekfile $file_name : OK "
	else
		echo "need file : $file_name"
		echo "download file : "
		wget --no-check-certificate -t 6 --timeout 180 $file_url -O packages/$file_name
		if [ $? -eq 0 ]
		then
			echo "download $file_name finished "
		else
			rm $file_name
			echo "### ERROR ####"
			echo "$file_name get error ... try to change other version of webpy ."
			exit
		fi
	fi
}

mkdir -p packages
check_file "web.py-0.33.tar.gz" "http://webpy.org/static/web.py-0.33.tar.gz"
check_file "requests-2.7.0.tar.gz" "https://pypi.python.org/packages/source/r/requests/requests-2.7.0.tar.gz#md5=29b173fd5fa572ec0764d1fd7b527260"

docker build -t qdocker/webpy:7 .
