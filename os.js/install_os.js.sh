#!/bin/sh

mkdir /app
cd /app
git clone https://github.com/os-js/OS.js.git
cd OS.js
source /root/.bashrc
npm install grunt-cli -g
npm install
grunt --force

#binPath="/os.js/bin"
#echo "PATH=\$PATH:$binPath" >> /etc/bashrc
