FROM centos

RUN yum -y install epel-release.noarch 
RUN yum -y update && yum -y install \
        sudo.x86_64 \
        git.x86_64 \
        make.x86_64 \
        gcc.x86_64 \
        ruby.x86_64 \
        ruby-devel.x86_64 \
        libicu.x86_64 \
        libicu-devel.x86_64 \
        patch-2.7.1-8.el7.x86_64 \
        gcc-c++.x86_64 \
        zlib-devel.x86_64 \
        cmake.x86_64 \
        mariadb-devel.x86_64 \
        nodejs.x86_64 \
        redis.x86_64 \
        golang.x86_64

RUN adduser -r git  && mkdir -p /home/git && chown -R git:git /home/git
RUN cp /etc/sudoers /etc/sudoers_ori \
        && echo "git  ALL=(ALL)   NOPASSWD: ALL" >> /etc/sudoers \
        && sed -i \
            -e 's/Defaults    requiretty/#Defaults    requiretty/' \
            -e 's#Defaults    secure_path = /sbin:/bin:/usr/sbin:/usr/bin#&:/usr/local/bin#' \
            /etc/sudoers

RUN sudo -u git -H git clone https://github.com/gitlabhq/gitlabhq.git /home/git/gitlab

WORKDIR /home/git/gitlab

RUN sudo -u git -H cp config/gitlab.yml.example config/gitlab.yml \
         && sudo -u git -H cp config/unicorn.rb.example config/unicorn.rb \
         && sudo -u git -H cp config/initializers/rack_attack.rb.example config/initializers/rack_attack.rb \
         &&  cp lib/support/init.d/gitlab /etc/init.d/gitlab &&  chmod +x /etc/init.d/gitlab

#chown -R git:git {log,tmp}
#chmod -R u+rwX {log,tmp}
#chmod -R u+rwX tmp/{pids,sockets}

RUN sudo -u git -H git config --global user.name "GitLab" \
 && sudo -u git -H git config --global user.email "gitlab@localhost" \
 && sudo -u git -H git config --global core.autocrlf input 


## mysql config
RUN sudo -u git -H cp config/database.yml.mysql config/database.yml \
 && sudo -u git -H sed -i -e 'N;s#username: git\n  password: "secure password"#username: git\n  password: git#' \
    -e  's/# host: localhost/host: mysql\n  port: 3306/' \ 
    config/database.yml \
 && sudo -u git -H sed -i 's~ask_to_continue~#&~' lib/tasks/gitlab/setup.rake \
 && sudo -u git -H sed -i 's#127.0.0.1:8080#0.0.0.0:8080#' config/unicorn.rb \
 && sudo -u git -H chmod o-rwx config/database.yml

#### config gem need root
RUN gem sources --remove https://rubygems.org/ \
    && gem sources -a https://ruby.taobao.org/  \
    && gem install bundler --no-rdoc --no-ri 

RUN sed -i 's#https://rubygems.org#https://ruby.taobao.org#' Gemfile \
    && gem sources --remove https://rubygems.org/ \
    && gem sources -a https://ruby.taobao.org/

RUN sudo -u git -H env PATH=$PATH:/usr/local/bin bundle install --deployment --without development test postgres aw

RUN sudo -u git -H git clone https://gitlab.com/gitlab-org/gitlab-workhorse.git /home/git/gitlab-workhorse && cd /home/git/gitlab-workhorse &&  make && make install

RUN sudo -u git -H git clone http://github.com/gitlabhq/gitlab-shell.git /home/git/gitlab-shell

COPY gitlab-entrypoint.sh /home/git/gitlab/
RUN chown git:git /home/git/gitlab/gitlab-entrypoint.sh && chmod +x /home/git/gitlab/gitlab-entrypoint.sh
ENTRYPOINT /home/git/gitlab/gitlab-entrypoint.sh && tail -f /home/git/gitlab/log/gitlab-workhorse.log
