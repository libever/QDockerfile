#!/bin/sh

# install mysql
docker run --name mysql -e MYSQL_ROOT_PASSWORD=root -d mysql/mysql-server:5.6.27

# install redis
docker run --name redis -d redis

#install gitlab
docker build -t yantao473/gitlab .

docker run --name gitlab_v -p 8080:8080 --link mysql:mysql --link redis:redis yantao473/gitlab 
