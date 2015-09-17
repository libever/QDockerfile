#!/bin/sh

d=$(greadlink -f ../code)
dparams="--name nginx -i -t -p 8000:80 -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockerwebpy docker run $dparams qdocker/webpy:7 

