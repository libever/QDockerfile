#!/bin/sh

screen -S dockernginx docker run -i -t qdocker/php5:7 -p 9000 
