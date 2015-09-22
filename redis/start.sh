#!/bin/sh

SYSTEM=$(uname -s)
if [ $SYSTEM == "Darwin" ] 
then
	vdir=$(greadlink -f "../code/dockerredis")	
else
	vdir=$(readlink -f "../code/dockerredis")	
fi
mkdir -p $vdir
dparams="--name redis -i -t -p 8001:6379 -v $vdir:/blackhole"
screen -S dockerredis docker run $dparams qdocker/redis:7 
