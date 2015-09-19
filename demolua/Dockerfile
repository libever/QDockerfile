FROM qdocker/base:7
RUN mkdir /sw
ADD lua-5.3.1.tar.gz /sw/
ADD install_demolua.sh /sw/install_demolua.sh

RUN yum install -y readline-devel.x86_64
RUN /bin/sh /sw/install_demolua.sh

ENTRYPOINT /bin/bash

