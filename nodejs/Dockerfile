FROM qdocker/base:7
RUN yum install -y gcc-c++
RUN mkdir /sw
ADD node-v0.10.35.tar.gz /sw/
ADD install_nodejs.sh /sw/install_nodejs.sh
RUN /bin/sh /sw/install_nodejs.sh

ENTRYPOINT /bin/bash

