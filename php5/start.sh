#!/bin/sh

d=$(readlink -f ../code)
dparams="--name php5 -i -t -p 9000  -v $d:/code"
dparams="$dparams --privileged=true "
screen -s dockernginx docker run $dparams qdocker/php5:7 
#docker run $dparams qdocker/php5:7
