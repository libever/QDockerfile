#!/bin/sh

cd /home/git/gitlab
PIDFILE=/home/git/gitlab/tmp/pids/gitlabs.pid

if [ ! -s $PIDFILE ]
then
     # mysql init
     # 'CREATE DATABASE IF NOT EXISTS `gitlabhq_production`'
     # 'GRANT ALL PRIVILEGES ON `gitlabhq_production`.* TO "git"@"%" IDENTIFIED BY "git"'
     # 'FLUSH PRIVILEGES'
     echo -e "init database .... \n"
		 ##mysql -u root -proot -h mysql -e "CREATE DATABASE IF NOT EXISTS gitlabhq_production"
		 ##mysql -u root -proot -h mysql -e 'GRANT ALL PRIVILEGES ON gitlabhq_production.* TO "git"@"%" IDENTIFIED BY "git";FLUSH PRIVILEGES;' 
     sudo -u git -H bundle exec rake gitlab:shell:install[v$(cat /home/git/gitlab-shell/VERSION)] REDIS_URL=redis://redis:6379 RAILS_ENV=production
     sudo -u git -H bundle exec rake gitlab:setup RAILS_ENV=production GITLAB_ROOT_PASSWORD='5iveL!fe'
     sudo -u git -H bundle exec rake gitlab:env:info RAILS_ENV=production
     sudo -u git -H bundle exec rake assets:precompile RAILS_ENV=production
     sudo -u git -H find /home/git/gitlab -type f \( -name "*.rb" -o -name "*.rake" \) | xargs sed -i 's#redis://localhost:6379#redis://redis:6379#'
fi
/etc/init.d/gitlab start && cat /home/git/gitlab/tmp/pids/{gitlab-workhorse.pid,sidekiq.pid,unicorn.pid} > $PIDFILE
