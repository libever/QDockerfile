#!/bin/sh

#ulimit -c unlimited

docker run -w /ccode --name myhttpd -it --privileged=true -p 80:1028 -v /Users/xingyue/outcode/git/lovely-codes/QDockerfile/ccode/:/ccode/ qdocker/base:7 /bin/bash
