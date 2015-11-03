#!/bin/sh

#ulimit -c unlimited


r=$(docker exec myhttpd /bin/sh -c "echo OK" 2>&1 )
if [ "$r" == "OK" ]
then
	echo "running ...."
elif [[ "$r" =~ "no such id" ]]
then
	docker run -w /ccode/myhttpd --name myhttpd -it --privileged=true -p 80:1028 -v /Users/xingyue/outcode/git/lovely-codes/QDockerfile/ccode/:/ccode/ qdocker/base:7 /bin/bash
else
docker start myhttpd && docker attach myhttpd
fi

