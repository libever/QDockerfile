#!/bin/sh

alias quickget='mytget -n 20 '
KEY=""
quickget $(curl -s "http://1.anyapi.sinaapp.com/scs/durl.php?file=$1&KEY=$KEY")
