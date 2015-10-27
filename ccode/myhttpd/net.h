#ifndef MYHTTPD_NET_H
#define MYHTTPD_NET_H

#include "common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef enum RequestType {POST,GET,NONE} RequestType ;

typedef struct NetServer {
	int serverSocket;
	struct sockaddr_in bindAddress;
	int process_born;
	char document_root[128];
} NServer;

typedef struct NetClient {
	int clientSocket;
	struct sockaddr_in clientAddress;
	RequestType rt ;
	char requestUrl[256]; 
	char queryString[512];
	char *postData;
	NServer *server;
	char filetype[5];
	BOOL isCgi;
} NClient ;

typedef void (*loopHanlder)(NServer*);

void openServer(NServer *myServer);
void closeServer(NServer *myServer);
void loopServer(NServer *myServer ,loopHanlder handler);
NServer* initNServer(int port,int process_born,char* document_root);
int readLine(NClient *client,char* buf,int size);
int readSize(NClient *client,char* buf,int size);
int writeData(NClient *client,char* buf,int size);
NClient * readMyClient(NServer *myServer,int seconds);
BOOL initClientMethodAndUrl(NClient *,char*);
void freeClient(NClient *client);

#endif
