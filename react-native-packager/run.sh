#!/bin/bash

d=$(pwd)

jsdir=$d/js

docker stop packager
docker rm packager

docker run --privileged=true -it -v $jsdir:/app/js -p 8081:8081 --name packager packager /bin/bash /app/runapp.sh
