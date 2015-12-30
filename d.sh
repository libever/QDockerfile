#!/bin/bash

curl -s  "https://raw.githubusercontent.com/lovely-codes/QDockerfile/master/$1/Dockerfile" > Dockerfile

for u in $(curl -s "https://raw.githubusercontent.com/lovely-codes/QDockerfile/master/$1/build.sh" | grep need | awk '{print $2}')
do
	wget --no-check-certificate $u
done
