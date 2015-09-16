#!/bin/sh

SYSTEM=`uname -s` 
if [  $SYSTEM = "Darwin" ] 
then
	d=$(greadlink -f ../code)
else 
	d=$(readlink -f ../code)
fi

dparams="--name golang -i -t -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockergolang docker run $dparams qdocker/golang:7 
