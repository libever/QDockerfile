#!/bin/sh

mkdir download
cd download

wget  http://download.openvz.org/template/precreated/centos-7-x86_64.tar.gz
cat centos-7-x86_64.tar.gz | docker import - xcentos:7
docker run -i -t xcentos:7 /bin/sh

git clone https://github.com/lovely-codes/QDockerfile.git

cd QDockerfile

cd nginx
pwd
sh build.sh
cd ..

cd php5
pwd
sh build.sh
cd ..

cd mysql5.6
pwd
sh build.sh
