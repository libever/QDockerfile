#!/bin/sh

image_name="qdocker/redis"
tag="7"
docker rm -f $(docker ps -a | grep $image_name | awk '{print $1}')
docker rmi -f $image_name:$tag
sh build.sh

