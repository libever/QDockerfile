#!/bin/bash

yum install docker
git clone https://github.com/lovely-codes/QDockerfile.git
/bin/sh QDockerfile/create_xcentos7.sh
cd QDockerfile/base
sh build.sh
