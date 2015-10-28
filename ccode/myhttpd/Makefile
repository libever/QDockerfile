all: myhttpd 

myhttpd: myhttpd.c net.o handler.o config.o color.o mycgi.o
	gcc -g -W -Wall  -lpthread -o myhttpd myhttpd.c net.o handler.o config.o color.o mycgi.o

net.o:net.c net.h
	gcc -g -W -Wall -c net.c

handler.o:handler.c handler.h
	gcc -g -W -Wall -c handler.c

color.o:color.c color.h
	gcc -g -W -Wall -c color.c

config.o:config.c config.h common.h
	gcc -g -W -Wall -c config.c

mycgi.o:mycgi.c mycgi.h common.h
	gcc -g -W -Wall -c mycgi.c

clean:
	rm myhttpd *.o
	rm -rf myhttpd.dSYM
