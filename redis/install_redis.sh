#!/bin/sh

cd /sw

cd redis-3.0.0/src
sed -i 's/PREFIX?=\/usr\/local/PREFIX?=\/redis/g' Makefile
make USE_TCMALLOC=yes
make install

cd /redis
mkdir etc
cd etc
cp /sw/redis-3.0.0/redis.conf .

sed -i 's/daemonize no/daemonize yes/g' redis.conf

#cat redis.conf | grep daemonize
