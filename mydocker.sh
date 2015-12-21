#!/bin/bash

yum install docker
systemctl enable docker.service
systemctl start docker.service
git clone https://github.com/lovely-codes/QDockerfile.git
/bin/sh QDockerfile/create_xcentos7.sh
cd QDockerfile/base
sh build.sh
