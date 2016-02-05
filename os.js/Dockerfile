FROM qdocker/nodejs_use_nvm:7
RUN mkdir /sw

ADD install_os.js.sh /sw/install_os.js.sh
RUN /bin/sh /sw/install_os.js.sh

ENTRYPOINT /bin/bash
