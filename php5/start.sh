#!/bin/sh

d=$(pwd)
dparams="-i -t -p 9000  -v $d/code:/code"
dparams="$dparams --privileged=true "
screen -s dockernginx docker run $dparams qdocker/php5:7 
#docker run $dparams qdocker/php5:7 
