FROM qdocker/base:7
RUN mkdir /sw
ADD nginx-1.9.3.tar.gz /sw/
ADD install_nginx.sh /sw/install_nginx.sh
ADD nginx.conf /sw/nginx.conf
RUN /bin/sh /sw/install_nginx.sh
RUN yum install -y git.x86_64
RUN mkdir -p /sw/tools/ngx_tool && git clone https://github.com/qixingyue/ngx_tool.git /sw/tools/ngx_tool

ENTRYPOINT /nginx/sbin/nginx



