#!/bin/bash

[ -d "/nginx/html/upload" ] && chown -R nobody:nobody /nginx/html/upload
[ ! -d "/nginx/html/upload" ] && echo "NO UPLOAD DIR"

echo "OK"
