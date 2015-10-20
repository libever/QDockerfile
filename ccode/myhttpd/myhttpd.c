#include "myhttpd.h"
#include "common.h"
#include "net.h"
#include "handler.h"

void StopServer(){
	closeServer(myServer);
}

int main(){
	int port = 1028;

	myServer = initNServer(port);
	signal(SIGINT, StopServer); 
	printf("INIT server at %d \n",port);
	openServer(myServer);
	loopServer(myServer,loopMainHandler);
	StopServer();

	return 0;
}
