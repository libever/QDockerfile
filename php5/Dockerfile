FROM qdocker/base:7

RUN mkdir /sw
ADD php-5.4.20.tar.gz /sw/
ADD ./install_fpm.sh /sw/install_fpm.sh
RUN yum install -y bison-devel.x86_64
RUN /bin/bash /sw/install_fpm.sh

ENTRYPOINT /php5/sbin/php-fpm 



