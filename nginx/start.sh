#!/bin/sh

SYSTEM=`uname -s` 
if [  $SYSTEM = "Darwin" ] 
then
    d=$(greadlink -f ../code)
else 
    d=$(readlink -f ../code)
fi

dparams="--name nginx -d -p 10080:80 -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockernginx docker run $dparams qdocker/nginx:7 
