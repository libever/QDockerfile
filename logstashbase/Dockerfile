FROM pri.docker:5000/miniwithsshd

RUN yum update -y
RUN yum install  ruby-devel  rubygems-devel  java-1.8.0-openjdk-devel -y
RUN gem sources --remove https://rubygems.org/
RUN gem sources -a https://ruby.taobao.org/
RUN gem install bundler

