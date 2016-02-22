#!/bin/bash

echo "NEED golang 1.5 "

git clone https://github.com/chrislusf/seaweedfs.git

cd seaweedfs

P=$(pwd)

mkdir -p $GOPATH/src/golang.org/x
cd $GOPATH/src/golang.org/x

git clone https://github.com/golang/net.git
git clone https://github.com/golang/image.git

cd $P
make
