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
Add set_root_pwd.sh /sw/set_root_pwd.sh
RUN /bin/bash /sw/set_root_pwd.sh

ENTRYPOINT /mysql5/bin/mysqld_safe --defaults-file=/mysql5/my.cnf
