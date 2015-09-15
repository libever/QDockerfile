#!/bin/sh

SYSTEM=`uname -s` 
if [  $SYSTEM = "Darwin" ] 
then
	d=$(greadlink -f ../code)
else 
	d=$(readlink -f ../code)
fi

dparams="--name nodejs -i -t -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockernodejs docker run $dparams qdocker/nodejs:7 
