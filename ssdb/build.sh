#!/bin/sh

#need https://github.com/ideawu/ssdb/archive/master.zip

#https://github.com/ideawu/ssdb
#wget --no-check-certificate https://github.com/ideawu/ssdb/archive/master.zip
docker build -t qdocker/ssdb:7 .
