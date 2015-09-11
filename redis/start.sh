#!/bin/sh

dparams="--name redis -i -t -p 8001:6379 "

screen -S dockerredis docker run $dparams qdocker/redis:7 
