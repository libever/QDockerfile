#include "handler.h"
#include "common.h"
#include <pthread.h>
#include <time.h>


static pid_t currentPid;

void loopMainHandler(NServer *myServer) {
	NClient *client;
	pthread_t newthread;
	int process_count = 0;
	int process_born = myServer->process_born;
	pid_t fpid;
	pid_t pids[process_born];
	for ( ; process_count < process_born ; process_count++) {
		fpid = fork();
		if (fpid < 0 ) {
			ExitMessage("fork failed");
		} else if (fpid > 0) {
			pids[process_count] = fpid;
		} else {
			currentPid = getpid();
			while(1){
				client = readMyClient(myServer,90);		
				if(pthread_create(&newthread , NULL, loopRequest, (void *) client) != 0) {
					ExitMessage("thread create failed ... ");
				}
			}
		}
	}
	for( process_count = 0 ; process_count < process_born ; process_count++ ) {
		waitpid(pids[process_count],NULL,0);	
	}
	//主进程自行退出
	if(currentPid == 0 ) exit(0);
}

void * loopRequest(void *arg){
	NClient *client = (NClient *) arg;
	char buf[256] = {'\0'};
	int bufsize = sizeof(buf);
	int handlerIndex = 0 , requestRes = 0;
	int (*handlerList[])(NClient *)  = {
		handleBySendFileContent,
		handlerGetRequest,
		handlerPostRequest,
		notFindRequest,
		NULL};
	int (*handler)(NClient *) = handlerList[0];

	bzero(buf,bufsize);
	if( ( bufsize - 1 ) ==  readLine(client,buf,bufsize)){
		infoClient(client,"URL IS TOO LONG ... \n",CONTENT_TYPE_HTML);			
	} else {
		if(FALSE == initClientMethodAndUrl(client,buf)){
			infoClient(client,"URL IS TOO SHORT",CONTENT_TYPE_HTML);
		} else {
			do{
				requestRes = handler(client);
				switch(requestRes) {
					case HANDLED:
						handler = NULL;
						break;
					case CONTINUE:
						handler = handlerList[++handlerIndex];
						break;
					default :
						ExitMessage("NO RULES FOR HANDLER REQUEST");
				}
			} while (handler !=  NULL );
		}
	}

	freeClient(client);
	return NULL;
}

int handleBySendFileContent(NClient *client){
	char file_path[128] = {'\0'};
	char message[256];
	char **contentList = (char**)malloc(sizeof(char*) * 64);
	char **listPos = contentList;

	*listPos = (char*) malloc(sizeof(char) * 128);
	sprintf(*listPos,"%s%s",client->server->document_root,client->requestUrl);

	listPos++;
	*listPos = (char*) malloc(sizeof(char) * 128);
	sprintf(*listPos,"%s%s",client->server->document_root,client->requestUrl);

	listPos++;
	*listPos = (char*) malloc(sizeof(char) * 128);
	sprintf(*listPos,"%s%s",client->server->document_root,client->requestUrl);

	listPos++;
	*listPos = NULL;

	sprintf(message,"FIND FILE >>>> Hello world FROM %d \n URL IS %s\n ",currentPid,client->requestUrl);
	/*infoClientList(client,contentList,CONTENT_TYPE_HTML);*/
	/*return HANDLED;*/
	return CONTINUE;
}

int handlerGetRequest(NClient* client) {
	char message[128] = {'\0'};
	sprintf(message,"Hello world FROM %d \n URL IS %s\n ",currentPid,client->requestUrl);
	/*infoClient(client,message,CONTENT_TYPE_HTML);*/
	return CONTINUE;
}

int handlerPostRequest(NClient* client) {
	return CONTINUE;
}

int cgiRequest(NClient* client) {
	return CONTINUE;
}

void infoClientList(NClient *client,char** messageList,char* contentType) {
	char **scanPos = messageList;
	char text[2048] = {'\0'};
	int messageLength = 0;
	char *messageTpl = "HTTP/1.1 200 OK\r\n\
Server: myhttp\r\n\
Connection: closed \r\n\
Content-Type: %s\r\n\
Content-Length: %d \r\n\
\r\n";

	do {
		messageLength += strlen(*scanPos);	
		scanPos++;
	} while(*scanPos != NULL);

	scanPos = messageList;
	sprintf(text,messageTpl,contentType,messageLength);
	writeData(client,text,strlen(text));
	do {
		writeData(client,*scanPos,strlen(*scanPos));
		scanPos++;
	} while(*scanPos != NULL);

	//清理之前malloc的内容资源	
	scanPos = messageList;
	do {
		free(*scanPos);
		scanPos++;
	} while(*scanPos != NULL);
	free(messageList);
}

void infoClient(NClient *client,char* message,char* contentType) {
	char text[2048] = {'\0'};
	int messageLength = strlen(message) ;
	char *messageTpl = "HTTP/1.1 200 OK\r\n\
Server: myhttp\r\n\
Connection: closed \r\n\
Content-Type: %s\r\n\
Content-Length: %d \r\n\
\r\n\
%s";
	sprintf(text,messageTpl,contentType,messageLength,message);
	writeData(client,text,strlen(text));
}

int notFindRequest(NClient *client) {
		char *notFindMessage = "<h1>Sorry I can't find your file . </h1>";
		char text[2048] = {'\0'};
		char *messageTpl = "HTTP/1.1 404 Not Found\r\n\
Server: myhttp\r\n\
Content-Type: %s \r\n\
Content-Length: %d \r\n\
Connection: closed \r\n\
\r\n\
%s";
		sprintf(text,messageTpl,CONTENT_TYPE_HTML,strlen(notFindMessage),notFindMessage);
		writeData(client,text,strlen(text));
	return HANDLED;
}
