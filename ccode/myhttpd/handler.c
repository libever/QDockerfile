#include "handler.h"
#include "common.h"

void loopMainHandler(NServer *myServer) {
	int i ; 
	char buf[256] = {'\0'};
	NClient *client;

	for(i = 1 ; i < 10 ; i++){
		printf("new connection ...\n");
		client = readMyClient(myServer,3);			
		readLine(client,buf,256);
		printf("%s\n",buf);
		freeClient(client);
	}
}

void handlerGetRequest(NServer *myServer) {

}

void handlerPostRequest(NServer *myServer) {

}

void cgiRequest(NServer *myServer) {

}


