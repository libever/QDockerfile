#ifndef MYHTTPD_NET_H
#define MYHTTPD_NET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct NetServer {
	int serverSocket;
	struct sockaddr_in bindAddress;
} NServer;

typedef struct NetClient {
	int clientSocket;
	struct sockaddr_in clientAddress;
} NClient ;

typedef void (*loopHanlder)(NServer*);

void openServer(NServer *myServer);
void closeServer(NServer *myServer);
void loopServer(NServer *myServer ,loopHanlder handler);
NServer* initNServer(int port);
int readLine(NClient *myServer,char* buf,int size);
int readSize(NClient *myServer,char* buf,int size);
int writeData(NClient *myServer,char* buf,int size);
NClient * readMyClient(NServer *myServer,int seconds);
void freeClient(NClient *client);

#endif
