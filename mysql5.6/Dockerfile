FROM qdocker/base:7
RUN mkdir /sw
RUN yum install -y cmake.x86_64
ADD mysql-5.6.21.tar.gz /sw/
ADD install_mysql.sh /sw/install_mysql.sh
RUN /bin/sh /sw/install_mysql.sh
#
#ENTRYPOINT /nginx/sbin/nginx && /bin/bash
#
#
#
