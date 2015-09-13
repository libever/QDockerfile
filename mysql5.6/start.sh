#!/bin/sh

d=$(readlink -f ../code)
dparams="--name mysql5 -i -t -p 8306:3306 -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockermysql docker run $dparams qdocker/mysql5:7 
