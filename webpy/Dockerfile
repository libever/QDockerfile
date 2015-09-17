FROM qdocker/base:7
RUN mkdir /sw

ADD web.py-0.33.tar.gz /sw/
ADD install_webpy.sh /sw/install_webpy.sh
RUN /bin/sh /sw/install_webpy.sh

ENTRYPOINT /bin/bash

