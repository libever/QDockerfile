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
	if(NULL != myServer) {
		free(myServer);
	}
}

void loopServer(NServer *myServer ,loopHanlder handler) {
	handler(myServer);
}

NServer* initNServer(int port, int process_born,char* document_root) {
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
	newServer->process_born= process_born;
	memcpy(newServer->document_root,document_root,strlen(document_root));

	return newServer;
}

int readLine(NClient *client,char* buf,int size) {
	int pos = 0 ;
	char c = '\0';
	int res = 0;
	int lineEnd = 0;

	for( ; pos < ( size - 1 ) ; pos++){
		res = recv(client->clientSocket,&c,1,0);			
		if( res <= 0 ) {
			return res;	
		}
		buf[pos] = c;
		switch(c) {
			case '\r':
				break;	
			case '\n':
				lineEnd = 1;	
				break;
			default:
				if( pos != 0 && buf[pos-1] == '\r') {
					printf("D ERROR : ....\n");
					return -1;
				} 
		}
		if(1 == lineEnd) {
			break;	
		}
	} 
	buf[pos] = '\0';
	return pos;
}

int readSize(NClient *client,char* buf, int size) {
	return recv(client->clientSocket,buf,size,0);
}

int writeData(NClient *client,char* buf,int size) {
	return send(client->clientSocket,buf,size,0);
}

NClient * readMyClient(NServer *myServer,int seconds){
	NClient *newClient ;
	int timeoutres;
	struct timeval timeout = {seconds,0};
	int clientAddrSize = sizeof(newClient->clientAddress);

	newClient	= (struct NetClient *) malloc(sizeof(struct NetClient));
	newClient->clientSocket = accept(myServer->serverSocket,(struct sockaddr *)&newClient->clientAddress,(socklen_t *)&clientAddrSize);

	if(newClient->clientSocket == -1) {
		ExitMessage("accept failed ...");
	}
	timeoutres = setsockopt(newClient->clientSocket,SOL_SOCKET,SO_SNDTIMEO,(const char*)&timeout,sizeof(timeout));
	timeoutres = setsockopt(newClient->clientSocket,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
	newClient->rt = NONE ;
	bzero(newClient->requestUrl,256);
	newClient->server = myServer;

	return newClient;
}

BOOL initClientMethodAndUrl(NClient *client,char* firstLine) {
	char methods[4] = {'\0'};
	char *pos = firstLine;
	int insertPos = 0;
	while(*pos != ' ') {
		methods[insertPos++] = *pos;
		pos++;
	}

	if(methods[0] == 'g' || methods[0] == 'G') {
		client->rt = GET;	
	}

	if(methods[0] == 'p' || methods[0] == 'P') {
		client->rt = POST;	
	}

	if(client->rt == NONE){
		return FALSE;	
	}

	pos++;
	insertPos = 0;
	while(*pos != ' ') {
		client->requestUrl[insertPos++] = *pos;
		pos++;
	}

	if(strlen(client->requestUrl) == 0) {
		return FALSE;	
	}

	return TRUE;
}

void freeClient(NClient *client){
	close(client->clientSocket);
	if(NULL != client) {
		free(client);
	}
}
