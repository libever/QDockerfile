FROM qdocker/base:7

RUN mkdir /sw
ADD redis-3.0.0.tar.gz /sw/
ADD install_redis.sh /sw/
RUN /bin/sh /sw/install_redis.sh

ENTRYPOINT /redis/bin/redis-server /redis/etc/redis.conf 

