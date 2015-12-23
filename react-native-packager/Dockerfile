FROM qdocker/nodejs_use_nvm:7

RUN mkdir /app
RUN . /root/.bashrc && cd /app && react-native init rnapp
ADD ./runapp.sh /app/runapp.sh
WORKDIR /app
