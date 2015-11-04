#!/bin/sh

rsync -avzq 10.217.39.140::QDocker/ccode/myhttpd/* .

make clean
git add .
git commit -m "$1"
git push origin master

