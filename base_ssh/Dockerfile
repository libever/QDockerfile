FROM xcentos:7
RUN yum remove httpd -y
RUN yum update -y
RUN yum install -y gcc.x86_64 automake.noarch pcre-devel.x86_64 zlib-devel.x86_64 libxml2-devel.x86_64 git.x86_64 gdb.x86_64 strace.x86_64 libcurl-devel

ADD a.c /root/a.c
ADD a.sh /root/a.sh
ADD chinese_lang.sh /root/chinese_lang.sh
RUN /bin/sh /root/a.sh



## add sshd install in docker container .
RUN yum install -y openssh-server sudo
RUN sed -i 's/UsePAM yes/UsePAM no/g' /etc/ssh/sshd_config
RUN useradd admin 
RUN echo "admin:7c43568dd60fd7fa6e393d5341d011d7" | chpasswd
RUN echo "admin   ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN ssh-keygen -t dsa -f /etc/ssh/ssh_host_dsa_key
RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key
RUN mkdir /var/run/sshd
RUN mv /usr/bin/ssh /usr/bin/ssh_ori
ADD ssh_with_log /usr/bin/ssh 
RUN chmod a+x /usr/bin/ssh
