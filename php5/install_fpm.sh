#!/bin/sh

cd /sw/php-5.4.20
./configure --prefix=/php5 --enable-mysqlnd --with-mysql --with-mysqli --with-pdo-mysql --enable-fpm --enable-pcntl 
make 
make install
cp php.ini-development /php5/lib/php.ini
mv /php5/etc/php-fpm.conf.default /php5/etc/php-fpm.conf
sed -i "s/;daemonize = yes/daemonize = no/g" /php5/etc/php-fpm.conf



echo "#ADD PHP PATH" >> /etc/bashrc
echo "PATH=\$PATH:/php5/bin" >> /etc/bashrc
