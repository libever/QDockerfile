#!/bin/sh

SYSTEM=$(uname -s)
if [ $SYSTEM == "Darwin" ] 
then
	vdir=$(greadlink -f "../code/dockerphp5")	
else
	vdir=$(readlink -f "../code/dockerphp5")	
fi
mkdir -p $vdir
dparams="--name php5 -d -p 9000  -v $vdir:/blckhole -w /blackhole "
dparams="$dparams --privileged=true "

r=$(docker exec php5 /bin/sh -c "echo OK" 2>&1 )
if [ "$r" == "OK" ]
then
	echo "already running  "
	screen -x dockerphp5 
elif [[ "$r" =~ "no such id" ]]
then
  echo "not exist , not running , run  "
	screen -S dockerphp5 docker run $dparams qdocker/php5:7 
else
    echo "exist , not running , run and attach "
    screen -S dockerphp5 /bin/bash -c "docker start php5 && docker attach php5"
fi
