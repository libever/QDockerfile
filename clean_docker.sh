#!/bin/sh

docker rmi -f  $(docker images | grep "<none>" | awk '{print $3}')
docker rm -f $(docker ps -a | grep "Exit" | awk '{print $1}' )
