FROM qdocker/base:7
RUN yum install -y gcc-c++

RUN curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.29.0/install.sh | bash
RUN export NVM_DIR="/root/.nvm" && export NVM_NODEJS_ORG_MIRROR="https://npm.taobao.org/dist"  &&  [ -s "$NVM_DIR/nvm.sh" ] && . "$NVM_DIR/nvm.sh" &&  nvm install v5.0.0

RUN export NVM_DIR="/root/.nvm" && . "$NVM_DIR/nvm.sh" && nvm alias default v5.0.0
RUN . /root/.bashrc && npm install -g nrm && nrm use taobao && npm install -g react-native-cli
RUN . /root/.bashrc && react-native -v

ENTRYPOINT /bin/bash
