FROM qdocker/golang15:7
ADD ./weed-fs.sh /weed-fs/weed-fs.sh
WORKDIR /weed-fs
RUN /bin/bash /weed-fs/weed-fs.sh

EXPOSE 8080
EXPOSE 9333

ENV WEED_HOME /weed-fs/seaweedfs

ENTRYPOINT ["/weed-fs/seaweedfs/weed"]
