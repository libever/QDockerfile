#!/bin/sh

screen -S dockernginx docker run -i -t -p 9000 -v code:/code qdocker/php5:7 
