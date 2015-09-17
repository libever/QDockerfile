#!/bin/sh

image_name=$1
from_base="qdocker/base:7"

mkdir $image_name
touch $image_name/Dockerfile
touch $image_name/install_${image_name}.sh
touch $image_name/build.sh
touch $image_name/start.sh

cat > $image_name/Dockerfile <<EOF
FROM $from_base
RUN mkdir /sw

ADD install_${image_name}.sh /sw/install_${image_name}.sh
RUN /bin/sh install_${image_name}.sh

ENTRYPOINT /bin/bash

EOF

cat > $image_name/install_${image_name}.sh<<EOF
#!/bin/sh

EOF

cat > $image_name/start.sh<<EOF
#!/bin/sh

SYSTEM=`uname -s` 
if [  \$SYSTEM = "Darwin" ] 
then
	d=\$(greadlink -f ../code)
else 
	d=\$(readlink -f ../code)
fi



dparams="--name nginx -i -t -p 8000:80 -v \$d:/code"
dparams="\$dparams --privileged=true "
screen -S docker$image_name docker run \$dparams qdocker/$image_name:7 

EOF

cat > $image_name/build.sh<<EOF
#!/bin/sh

file_name=""
file_url=""

if [ -f \$file_name ] 
then
docker build -t qdocker/$image_name:7 .
else
echo "need file : \$file_name"
echo "download file : "
wget -t 3 --timeout 180 \$file_url
if [ \$? -eq 0 ]
then
	sh build.sh
else
	rm \$file_name
	echo "################"
	echo "\$file_name get error ... try to change other version of $image_name ."
fi
fi

EOF
