#!/bin/sh


containers=$(docker ps -a | tail -n +2 | awk -F "tcp" '{print $2}')

for c in $containers
do

echo $c
docker exec $c ip addr | grep eth0 | grep inet

echo ""

done
