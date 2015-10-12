FROM qdocker/base:7
RUN mkdir /sw

ADD install_tjserver.sh /sw/install_tjserver.sh
RUN /bin/sh /sw/install_tjserver.sh

ENTRYPOINT /bin/bash

