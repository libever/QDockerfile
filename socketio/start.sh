#!/bin/sh

SYSTEM=$(uname -s)
if [  $SYSTEM = "Darwin" ] 
then
    d=$(greadlink -f ../code)
else 
    d=$(readlink -f ../code)
fi

dparams="--name socketio -i -t -v $d:/code"
dparams="$dparams --privileged=true "
screen -S dockersocketio docker run $dparams qdocker/socketio:7 

