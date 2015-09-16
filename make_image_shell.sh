#!/bin/sh

image_name=$1

mkdir $image_name
touch $image_name/Dockerfile
touch $image_name/install_${image_name}_.sh
touch $image_name/build.sh
touch $image_name/start.sh

