#ifndef MYHTTPD_NET_H
#define MYHTTPD_NET_H

typedef struct NetServer {
	int serverSocket;
} NServer;

typedef void (*loopHanlder)(NServer);

void openServer(NServer);
void closeServer(NServer);
void loopServer(NServer,loopHanlder handler);
NServer initNServer(int);


#endif
