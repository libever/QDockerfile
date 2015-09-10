#!/bin/sh

screen -S dockernginx docker run -i -t qdocker/nginx:7 -p 8000:80
