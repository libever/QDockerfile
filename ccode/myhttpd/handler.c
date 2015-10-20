#include "handler.h"
#include "common.h"
#include <pthread.h>

void loopMainHandler(NServer *myServer) {
	NClient *client;
	pthread_t newthread;

	while(1){
		client = readMyClient(myServer,90);		
		/*loopRequest(client);*/
	 if(pthread_create(&newthread , NULL, loopRequest, (void *) client) != 0) {
			ExitMessage("thread create failed ... ");
		}
	}

}

void * loopRequest(void *arg){
	NClient *client = (NClient *) arg;
	char buf[256] = {'\0'};
	int bufsize = sizeof(buf);
	int handlerIndex = 0 ;
	int (*handlerList[])(NClient *)  = {handlerGetRequest,handlerPostRequest,NULL};
	int (*handler)(NClient *) = handlerList[0];

	bzero(buf,bufsize);
	if( ( bufsize - 1 ) ==  readLine(client,buf,bufsize)){
		infoClient(client,"URL IS TOO LONG ... \n");			
	} else {
		do{
			if ( HANDLED == handler(client) ){
				break;	
			}
			handler = handlerList[++handlerIndex];
		} while (handler !=  NULL);
	}

	freeClient(client);
	return NULL;
}

int handlerGetRequest(NClient* client) {
	infoClient(client,"Hello world");
	return HANDLED;
}

int handlerPostRequest(NClient* client) {
	printf("2s\n");
	return CONTINUE;
}

int cgiRequest(NClient* client) {
	printf("2s\n");
	return CONTINUE;
}

void infoClient(NClient *client,char* message) {
	char text[2048] = {'\0'};
	sprintf(text,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s",message);
	writeData(client,text,strlen(text));
}
