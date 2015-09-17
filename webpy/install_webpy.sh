#!/bin/sh

cd /sw/packages

for pakckageName in $(ls)
do
	tar zxf $pakckageName
done

for pdir in $(ls -F | grep "/$")
do
	d=$(pwd)
	echo $pdir
	cd $pdir
	python setup.py install
	cd $d
done
