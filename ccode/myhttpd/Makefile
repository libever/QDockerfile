params=-g -Wall -W

all: myhttpd

myhttpd: myhttpd.c net.o handler.o config.o color.o mycgi.o module.o
	gcc ${params}  -lpthread -o myhttpd myhttpd.c net.o handler.o config.o color.o mycgi.o module.o

net.o:net.c net.h
	gcc ${params} -c net.c

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

clean:
	rm myhttpd *.o
	rm -rf myhttpd.dSYM
	rm modules/*.o
	rm modules/*.so
