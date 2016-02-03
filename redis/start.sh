#!/bin/sh

SYSTEM=$(uname -s)
if [ $SYSTEM == "Darwin" ] 
then
	vdir=$(greadlink -f "../code/dockerredis")	
else
	vdir=$(readlink -f "../code/dockerredis")	
fi

mkdir -p $vdir
dparams="--name redis -d -p 8001:6379 -v $vdir:/blackhole "

r=$(docker exec redis /bin/sh -c "echo OK" 2>&1 )
#echo $r
if [ "$r" == "OK" ]
then
	echo "already running  "
	screen -x dockerredis
elif [[ "$r" =~ "no such id" ]]
then
   echo "not exist , not running , run  "
	 screen -S dockerredis docker run $dparams qdocker/redis:7 
else
    echo "exist , not running , run and attach "
    screen -S dockerredis /bin/bash -c "docker start redis && docker attach redis "
fi
