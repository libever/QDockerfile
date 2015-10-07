#!/bin/sh

image_name=$1
from_base="qdocker/base:7"


function makedir(){
	mkdir $image_name
	touch $image_name/Dockerfile
	touch $image_name/install_${image_name}.sh
	touch $image_name/build.sh
	touch $image_name/start.sh
	touch $image_name/clean.sh
}

function makeDockerfile(){

cat > $image_name/Dockerfile <<EOF
FROM $from_base
RUN mkdir /sw

ADD install_${image_name}.sh /sw/install_${image_name}.sh
RUN /bin/sh /sw/install_${image_name}.sh

ENTRYPOINT /bin/bash

EOF

}

function makeInstallImagesh(){
cat > $image_name/install_${image_name}.sh<<EOF
#!/bin/sh


binPath="/$image_name/bin"
echo "PATH=\\\$PATH:\$binPath" >> /etc/bashrc

EOF

}

function makeStartImagesh(){
cat > $image_name/start.sh<<EOF
#!/bin/sh

#custom_edit_code 

docker_name=$image_name
image_name=qdocker/$image_name:7
docker_name=$image_name
screen_name=docker\${docker_name}
blackhole_real_dir="../code/\$screen_name"
o_ports=" -p 9001:9001"

#end custom_edit_code 



SYSTEM=\$(uname -s)
if [ \$SYSTEM == "Darwin" ] 
then
	Greadlink=greadlink
else
	Greadlink=readlink
fi
vdir=\$(\$Greadlink -f \$blackhole_real_dir)	
echo \$vdir
mkdir -p \$vdir
dparams="--name \$docker_name -i -t \$o_ports  -v \$vdir:/blackhole -w /blackhole"
dparams="--privileged=true \$dparams"

r=\$(docker exec \$docker_name /bin/sh -c "echo OK" 2>&1 )
if [ "\$r" == "OK" ]
then
	echo "already running  "
	screen -x \$screen_name
elif [[ "\$r" =~ "no such id" ]]
then
   echo "not exist , not running , run  "
	 screen -S \$screen_name docker run \$dparams \$image_name
else
    echo "exist , not running , run and attach "
    screen -S \$screen_name /bin/bash -c "docker start \$docker_name && docker attach \$docker_name"
fi

EOF
}

function makeCleansh(){
cat > $image_name/clean.sh <<EOF
#!/bin/sh

docker rmi -f qdocker/$image_name:7

EOF
}

function makeBuildsh(){
cat > $image_name/build.sh <<EOF
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
}

function makeScript(){
	makeDockerfile
	makeCleansh
	makeBuildsh
	makeInstallImagesh
	makeStartImagesh
}


if [ "$2" == "remakescript" ] 
then
	echo "remake script"
	makeScript
	exit
elif [ "$2" == "" ] 
then
	makedir
	makeScript
fi


