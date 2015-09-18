#!/bin/sh

cat >> /sw/demo.py <<EOF

#!/usr/bin/env python
#coding=utf-8

import web

urls = ("/","Index")

class Index :
    def GET(self):
        return "Hello world"

app = web.application(urls,globals())
if __name__ == "__main__":
    app.run()
else :
    application = app.wsgifunc()

EOF

cd /sw/
python demo.py > r.log 2>&1 & 
