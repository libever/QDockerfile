FROM qdocker/base:7
RUN mkdir /sw
RUN yum install -y cmake.x86_64
RUN yum install -y gcc-c++ 
RUN yum install -y bison-2.7-4.el7.x86_64
RUN yum install -y ncurses-devel
ADD mysql-5.6.21.tar.gz /sw/
ADD install_mysql.sh /sw/mysql-5.6.21/install_mysql.sh
ADD my.cnf  /sw/mysql-5.6.21/my.cnf
RUN /bin/sh /sw/mysql-5.6.21/install_mysql.sh
RUN echo "nohup /mysql5/bin/mysqld_safe /mysql5/bin/mysqld_safe > /mysql5/run.log 2>&1 & " > /etc/rc.local

ENTRYPOINT /bin/bash /etc/rc.local && /bin/bash
