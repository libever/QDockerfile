#!/bin/sh

screen -S dockernginx docker run -i -t -p 8000:80  qdocker/nginx:7 
