my docker files do make some common environment.
=======
This is some images made by myself.
=======
Very base file named xcentos:7 is from tar.gz file , Make base shell is :
<pre>
<code>
wget  http://download.openvz.org/template/precreated/centos-7-x86_64.tar.gz
cat centos-7-x86_64.tar.gz | docker import - xcentos:7
docker run -i -t xcentos:7 /bin/sh
</code>
</pre>

*** 

curl -s "https://raw.githubusercontent.com/lovely-codes/QDockerfile/master/d.sh" | /bin/bash -s ssdb
docker build -t . ssdb
