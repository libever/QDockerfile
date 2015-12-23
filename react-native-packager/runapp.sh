#!/bin/bash

#容器内部,运行react-native start

source /root/.bashrc

alias cp="cp"

cp -a -r js/* rnapp/
cd rnapp

react-native start

sleep 3600
