all: httpd simpleclient

httpd: httpd.c
	gcc -W -Wall  -lpthread -o httpd httpd.c
simpleclient:	simpleclient.c
	gcc -W -Wall simpleclient.c -o simpleclient

clean:
	rm httpd simpleclient
