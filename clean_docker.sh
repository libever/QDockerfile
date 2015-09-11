#!/bin/sh

docker rmi $(docker images | grep "<none>" | awk '{print $3}')
docker rm $(docker ps -a | grep "Exit" | awk '{print $1}' )
