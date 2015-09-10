FROM xcentos:7
RUN yum update -y
RUN yum install -y gcc.x86_64
RUN yum install -y automake.noarch
RUN yum install -y pcre-devel.x86_64

ADD a.c /root/a.c
ADD a.sh /root/a.sh
RUN /bin/sh /root/a.sh

