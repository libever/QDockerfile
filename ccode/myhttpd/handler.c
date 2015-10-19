#include "handler.h"
#include "common.h"

void loopMainHandler(NServer *myServer) {
	char buf[256] = {'\0'};
	int bufsize = sizeof(buf);
	NClient *client;

	while(1){
		client = readMyClient(myServer,90);		
		bzero(buf,bufsize);
		if( ( bufsize - 1 ) ==  readLine(client,buf,bufsize)){
			infoClient(client,"URL IS TOO LONG ... \n");			
		} else {
				
		}
		freeClient(client);
	}

}

void handlerGetRequest(NServer *myServer) {

}

void handlerPostRequest(NServer *myServer) {

}

void cgiRequest(NServer *myServer) {

}

void infoClient(NClient *client,char* message) {
	char text[2048] = {'\0'};
	int messageLength = strlen(message);
	sprintf(text,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s",message);
	writeData(client,text,strlen(text));
}
