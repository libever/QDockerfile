FROM qdocker/base:7
RUN mkdir /sw

ADD install_demolua.sh /sw/install_demolua.sh
RUN /bin/sh /sw/install_demolua.sh

ENTRYPOINT /bin/bash

