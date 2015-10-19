#include "handler.h"
#include "common.h"

void loopMainHandler(NServer *myServer) {
	char buf[256] = {'\0'};
	int bufsize = sizeof(buf);
	NClient *client;
	int handlerIndex = 0 , dealed = 0;
	void (*handlerList[])(NClient *)  = {handlerGetRequest,handlerPostRequest,NULL};
	void (*handler)(NClient *) = handlerList[0];

	while(1){
		client = readMyClient(myServer,90);		
		bzero(buf,bufsize);
		if( ( bufsize - 1 ) ==  readLine(client,buf,bufsize)){
			infoClient(client,"URL IS TOO LONG ... \n");			
		} else {
			do{
				handler(client);
				handler = handlerList[++handlerIndex];
			} while (handler !=  NULL);
		}
		freeClient(client);
	}

}

void handlerGetRequest(NClient* client) {
	printf("1s\n");
}

void handlerPostRequest(NClient* client) {
	printf("2s\n");
}

void cgiRequest(NClient* client) {
	printf("2s\n");
}

void infoClient(NClient *client,char* message) {
	char text[2048] = {'\0'};
	int messageLength = strlen(message);
	sprintf(text,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s",message);
	writeData(client,text,strlen(text));
}
