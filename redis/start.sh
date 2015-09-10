#!/bin/sh

screen -S dockerredis docker run -i -t -p 8001:6379 qdocker/redis:7 
