all: myhttpd 

myhttpd: myhttpd.c net.o handler.o config.o
	gcc -g -W -Wall  -lpthread -o myhttpd myhttpd.c net.o handler.o config.o

net.o:net.c net.h
	gcc -g -W -Wall -c net.c

handler.o:handler.c handler.h
	gcc -g -W -Wall -c handler.c

config.o:config.c config.h common.h
	gcc -g -W -Wall -c config.c

clean:
	rm myhttpd *.o
	rm -rf myhttpd.dSYM
