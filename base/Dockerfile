FROM xcentos:7
RUN yum install -y gcc.x86_64
RUN yum install -y automake.noarch

ADD a.c /root/a.c
ADD a.sh /root/a.sh
RUN /bin/sh /root/a.sh

