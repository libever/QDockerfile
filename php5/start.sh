#!/bin/sh

screen -S dockernginx docker run -i -t -p 9000 qdocker/php5:7 
