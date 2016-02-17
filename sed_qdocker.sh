#!/bin/sh


find . -name "build.sh" | xargs sed -i 's/qdocker/pri.docker:5000/g'
find . -name "Dockerfile" | xargs sed -i 's/qdocker/pri.docker:5000/g'
