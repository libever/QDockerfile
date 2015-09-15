#!/bin/sh

cd /sw/mysql-5.6.21
echo "add mysql user"
useradd mysql -r -d /dev/null -s /sbinlogin

MYSQL_PREFIX=/mysql5

cmake \
-DCMAKE_INSTALL_PREFIX=$MYSQL_PREFIX \
-DDEFAULT_CHARSET=utf8 \
-DDEFAULT_COLLATION=utf8_general_ci \
-DWITH_EXTRA_CHARSETS=all \
-DWITH_MYISAM_STORAGE_ENGINE=1 \
-DWITH_INNOBASE_STORAGE_ENGINE=1 \
-DWITH_ZLIB=bundled \
-DWITH_READLINE=1 \
-DWITH_DEBUG=OFF \
-DENABLED_LOCAL_INFILE=1 \
-DENABLED_PROFILING=1 \
-DMYSQL_MAINTAINER_MODE=0 \
-DMYSQL_TCP_PORT=3306 \
-DMYSQL_DATADIR=$MYSQL_PREFIX/data \
-DMYSQL_UNIX_ADDR=$MYSQL_PREFIX/data/mysql.sock 

make 
make install

chmod u+x ./scripts/mysql_install_db.sh
mkdir -p $MYSQL_PREFIX/logs
mkdir -p $MYSQL_PREFIX/data
chown mysql:mysql -R $MYSQL_PREFIX/data
./scripts/mysql_install_db.sh --basedir="$MYSQL_PREFIX" --datadir="$MYSQL_PREFIX/data" --user=mysql
cp my.cnf $MYSQL_PREFIX/my.cnf

REPLACEPATH=${MYSQL_PREFIX//\//\\/}
sed_i="s/{MYSQL_PREFIX}/$REPLACEPATH/g"
sed -i $sed_i $MYSQL_PREFIX/my.cnf
