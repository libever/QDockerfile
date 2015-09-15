#!/bin/sh

SYSTEM=`uname -s` 
if [  $SYSTEM = "Darwin" ] 
then
	d=$(greadlink -f ../code)
else 
	d=$(readlink -f ../code)
fi


dparams="--name mysql56 -i -t -p 8306:3306 -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockermysql docker run $dparams qdocker/mysql56:7 
