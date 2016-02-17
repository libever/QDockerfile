FROM qdocker/golang:7
ADD go1.5.3.linux-amd64.tar.gz /sw/golang15/

ADD install_golang.sh /sw/golang15/install_golang.sh
RUN /bin/sh /sw/golang15/install_golang.sh
ENV GOROOT /sw/golang15/go
ENV PATH $OLD_PATH:$GOROOT/bin:$GOPATH/bin
RUN go version

#
#ENTRYPOINT /bin/bash
#

