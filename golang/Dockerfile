FROM qdocker/base:7
#RUN yum install -y gcc-c++
RUN mkdir /sw
ADD go1.4.3.tar.gz /sw/
ADD install_golang.sh /sw/install_golang.sh
RUN /bin/sh /sw/install_golang.sh

ENV GOROOT /sw/go
ENV GOPATH /gocode
ENV OLD_PATH $PATH
ENV PATH $PATH:$GOROOT/bin:$GOPATH/bin
ENV GOROOT_BOOTSTRAP $GOROOT

ENTRYPOINT /bin/bash

