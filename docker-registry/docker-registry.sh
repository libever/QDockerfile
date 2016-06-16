#!/bin/bash

cat > Dockerfile <<EOT
FROM qdocker/golang15:7

ENV DISTRIBUTION_DIR /gocode/src/github.com/docker/distribution
ENV GOPATH $DISTRIBUTION_DIR/Godeps/_workspace:$GOPATH
ENV DOCKER_BUILDTAGS include_rados include_oss include_gcs

WORKDIR $DISTRIBUTION_DIR
COPY . $DISTRIBUTION_DIR
COPY cmd/registry/config-dev.yml /etc/docker/registry/config.yml
RUN yum install -y librados2-devel
RUN make PREFIX=/gocode clean binaries

VOLUME ["/var/lib/registry"]
EXPOSE 5000
ENTRYPOINT ["registry"]
CMD ["/etc/docker/registry/config.yml"]
EOT

has_image(){
	docker images | grep "$1" | wc -l
}

c_dir=$(pwd)

[ ! -d "distribution" ] && git clone https://github.com/docker/distribution.git

if [ $( has_image "xcentos" ) == 0 ] 
then
	[ ! -f centos-7-x86_64.tar.gz ] && wget  http://download.openvz.org/template/precreated/centos-7-x86_64.tar.gz
	cat centos-7-x86_64.tar.gz | docker import - xcentos:7
else
	echo "xcentos image has installed ..."
fi

[ ! -d "QDockerfile" ] &&  git clone https://github.com/lovely-codes/QDockerfile.git

echo "build base image"
cd QDockerfile/base
sh build.sh
cd $c_dir

echo "build golang1.4 image"
cd QDockerfile/golang/
sh build.sh
cd $c_dir

echo "build golang1.5 image"
cd QDockerfile/golang1.5/
sh build.sh
cd $c_dir

echo "build registry image"
cd distribution

cp Dockerfile Dockerfile.bk
cp ../Dockerfile Dockerfile

mkdir -p  /var/lib/registry
docker build -t qdocker/registry .  && echo "BUILD FINISHED : RUN registry : " && echo "" &&  echo "docker run -d qdocker/registry " && echo "OR USE THIS CMD : " echo "docker run -d -e SETTINGS_FLAVOR=dev -e STORAGE_PATH=/tmp/registry -v /db/docker-images:/tmp/registry -p 5000:5000 registry"
