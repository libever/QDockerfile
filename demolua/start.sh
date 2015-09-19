#!/bin/sh

SYSTEM=Darwin 
if [  $SYSTEM = "Darwin" ] 
then
	d=$(greadlink -f ../code)
else 
	d=$(readlink -f ../code)
fi



dparams="--name demolua -i -t -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockerdemolua docker run $dparams qdocker/demolua:7 

