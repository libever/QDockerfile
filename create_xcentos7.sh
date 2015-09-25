#!/bin/sh

wget  http://download.openvz.org/template/precreated/centos-7-x86_64.tar.gz
cat centos-7-x86_64.tar.gz | docker import - xcentos:7
docker run -i -t xcentos:7 /bin/sh

