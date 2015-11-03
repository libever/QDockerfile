params=-g -Wall -W

all: myhttpd libmymodule

myhttpd: myhttpd.c net.o handler.o config.o color.o mycgi.o module.o react.o modules log.o
	gcc ${params}  -lpthread -ldl -o myhttpd myhttpd.c net.o handler.o config.o color.o mycgi.o module.o react.o log.o

net.o:net.c net.h
	gcc ${params}  -fPIC -c net.c

handler.o:handler.c handler.h
	gcc ${params} -c handler.c

color.o:color.c color.h
	gcc ${params} -c color.c

config.o:config.c config.h common.h
	gcc ${params} -c config.c

mycgi.o:mycgi.c mycgi.h common.h
	gcc ${params} -c mycgi.c

module.o:module.c module.h
	gcc ${params} -c module.c

react.o:react.c react.h
	gcc ${params} -fPIC -c react.c

log.o:log.c log.h
	gcc ${params} -fPIC -c log.c

libmymodule:react.o net.o log.o
	ar rcs libmymodule.a react.o net.o log.o

modules:libmymodule
	cd modules && make

clean:
	rm -f libmymodule.a
	rm -f myhttpd *.o
	rm -rf myhttpd.dSYM
	rm -f ./logs/l_*.log
	cd modules && make clean
