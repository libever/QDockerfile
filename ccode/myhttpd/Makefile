all: myhttpd 

myhttpd: myhttpd.c net.o handler.o
	gcc -g -W -Wall  -lpthread -o myhttpd myhttpd.c net.o handler.o

net.o:net.c net.h
	gcc -g -W -Wall -c net.c

handler.o:handler.c handler.h
	gcc -g -W -Wall -c handler.c

clean:
	rm myhttpd *.o
	rm -rf myhttpd.dSYM
