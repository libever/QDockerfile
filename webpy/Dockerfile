FROM qdocker/base:7
RUN mkdir -p /sw/packages

ADD packages /sw/packages
ADD install_webpy.sh /sw/install_webpy.sh
RUN /bin/sh /sw/install_webpy.sh

ENTRYPOINT /bin/bash

