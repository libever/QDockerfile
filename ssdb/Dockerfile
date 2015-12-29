FROM qdocker/base:7

RUN mkdir /sw
WORKDIR /sw
ADD ./master.zip /sw/
RUN unzip master.zip
RUN yum install -y gcc-c++.x86_64 
RUN cd ssdb-master && make && make install

RUN ls /usr/local/ssdb

ENTRYPOINT /usr/local/ssdb/ssdb-server /usr/local/ssdb/ssdb.conf && /bin/bash
