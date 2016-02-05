#!/bin/sh

adir=$(pwd)

[ ! -s "mysql-5.6.21.tar.gz" ] && echo "NEED FILES mysql-5.6.21.tar.gz " && exit

echo "NEED FILES centos-7-x86_64.tar.gz "
echo "We can help you download that."
echo "Any Key To Confirm : "
read a

mkdir download
[ -s "centos-7-x86_64.tar.gz" ] && mv centos-7-x86_64.tar.gz download
cd download

[  ! -s "centos-7-x86_64.tar.gz" ] && wget  http://download.openvz.org/template/precreated/centos-7-x86_64.tar.gz
cat centos-7-x86_64.tar.gz | docker import - xcentos:7

git clone https://github.com/lovely-codes/QDockerfile.git

cd QDockerfile

cd base 
pwd
sh build.sh
cd ..

cd nginx
pwd
sh build.sh
cd ..

cd php5
pwd
sh build.sh
cd ..

mv $adir/mysql-5.6.21.tar.gz mysql5.6

cd mysql5.6 && pwd && sh build.sh && cd ..  && cd docker-compose-projects/lnmp && docker-compose up -d 

