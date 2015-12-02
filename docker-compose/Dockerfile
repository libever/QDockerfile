FROM xcentos:7

#RUN curl https://copr.fedoraproject.org/coprs/eparis/kubernetes-epel-7/repo/epel-7/eparis-kubernetes-epel-7-epel-7.repo -o /etc/yum.repos.d/eparis-kubernetes-epel-7-epel-7.repo

RUN yum update -y
RUN yum install docker -y

#install setuptools
RUN wget --no-check-certificate "https://pypi.python.org/packages/source/s/setuptools/setuptools-12.0.3.tar.gz#md5=f07e4b0f4c1c9368fcd980d888b29a65"  &&  tar -xzvf setuptools-12.0.3.tar.gz && cd setuptools-12.0.3 && python setup.py install

#install pip
RUN wget --no-check-certificate "https://pypi.python.org/packages/source/p/pip/pip-1.5.4.tar.gz#md5=834b2904f92d46aaa333267f" &&  tar -xzvf pip-1.5.4.tar.gz && cd pip-1.5.4 && python setup.py install

RUN mkdir /root/.pip && \
    touch /root/.pip/pip.conf && \
    echo "[global]" >> /root/.pip/pip.conf && \
    echo "trusted-host=mirrors.aliyun.com" >> /root/.pip/pip.conf && \
    echo "index-url=http://mirrors.aliyun.com/pypi/simple/" >> /root/.pip/pip.conf
RUN pip install -U docker-compose

