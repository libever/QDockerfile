FROM xcentos:7
RUN yum update -y
RUN yum install -y gcc.x86_64 automake.noarch pcre-devel.x86_64 zlib-devel.x86_64 libxml2-devel.x86_64 git.x86_64 gdb.x86_64 strace.x86_64

ADD a.c /root/a.c
ADD a.sh /root/a.sh
RUN /bin/sh /root/a.sh

