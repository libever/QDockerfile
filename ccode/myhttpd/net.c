#include "net.h"
#include "common.h"

void openServer(NServer *myServer) {
	if (bind(myServer->serverSocket, (struct sockaddr *)&myServer->bindAddress, sizeof(myServer->bindAddress)) < 0) {
		ExitMessage("bind failed ");
	}
	if (listen(myServer->serverSocket, 128) < 0) {
		ExitMessage("listen failed ");
	}
}

void closeServer(NServer *myServer) {
	close(myServer->serverSocket);	
	free(myServer);
}

void loopServer(NServer *myServer ,loopHanlder handler) {
	handler(myServer);
}

NServer* initNServer(int port) {
	NServer *newServer = (NServer*)malloc(sizeof(NServer));
	struct sockaddr_in name;
	int on = 1, ret;

	newServer->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (newServer->serverSocket == -1) {
		ExitMessage("socket create error ");
	}

	ret = setsockopt(newServer->serverSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	newServer->bindAddress = name;

	return newServer;
}

int readLine(NClient *client,char* buf,int size) {
	int n;
	n = recv(client->clientSocket, buf, size , 0);
	return n;
}

int writeLine(NClient *client,char* buf,int size) {
	return size;
}

NClient * readMyClient(NServer *myServer,int seconds){
	NClient *newClient ;
	int socket;
	int timeoutres;
	struct timeval timeout = {seconds,0};
	int clientAddrSize = sizeof(newClient->clientAddress);

	newClient	= (struct NetClient *) malloc(sizeof(struct NetClient));
	newClient->clientSocket = accept(myServer->serverSocket,&newClient->clientAddress,&clientAddrSize);

	if(newClient->clientSocket == -1) {
		ExitMessage("accept failed ...");
	}
	timeoutres = setsockopt(newClient->clientSocket,SOL_SOCKET,SO_SNDTIMEO,(const char*)&timeout,sizeof(timeout));
	timeoutres = setsockopt(newClient->clientSocket,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));

	return newClient;
}

void freeClient(NClient *client){
	close(client->clientSocket);
	free(client);
}
