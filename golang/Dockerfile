FROM qdocker/base:7
#RUN yum install -y gcc-c++
RUN mkdir /sw
ADD go1.4.2.linux-amd64.tar.gz /sw/
ADD install_golang.sh /sw/install_golang.sh
RUN /bin/sh /sw/install_golang.sh

ENTRYPOINT /bin/bash

