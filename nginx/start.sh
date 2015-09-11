#!/bin/sh

d=$(readlink -f ../code)
dparams="--name nginx -i -t -p 8000:80 -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockernginx docker run $dparams qdocker/nginx:7 
