#!/bin/sh


/mysql5/bin/mysqld_safe --defaults-file=/mysql5/my.cnf & 

sleep 5

/mysql5/bin/mysql -u root -p -e "grant all privileges on *.* to root@'%' identified by '123' with grant option;"
