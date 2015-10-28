#include "handler.h"
#include "common.h"
#include "config.h"
#include "mycgi.h"
#include <pthread.h>
#include <time.h>
#include<sys/stat.h>

static pid_t currentPid;

void loopMainHandler(NServer *myServer) {
	NClient *client;
	pthread_t newthread;
	int process_count = 0;
	int process_born = myServer->process_born;
	pid_t fpid;
	pid_t pids[process_born];

	if(TRUE == Config.DEBUG) {
		currentPid = getpid();
		while(1){
			client = readMyClient(myServer,90);		
			if(pthread_create(&newthread , NULL, loopRequest, (void *) client) != 0) {
				ExitMessage("thread create failed ... ");
			}
		}
	} else {
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
}

void * loopRequest(void *arg){
	NClient *client = (NClient *) arg;
	char buf[256] = {'\0'};
	int bufsize = sizeof(buf);
	int handlerIndex = 0 , requestRes = 0;
	int (*handlerList[])(NClient *)  = {
		handlePathPermission,
		handleFilePermission,
		handleBySendFileContent,
		handlePostData,
		cgiRequest,
		notFindRequest,
		NULL};
	int (*handler)(NClient *) = handlerList[0];

	bzero(buf,bufsize);
	if( ( bufsize - 1 ) ==  readLine(client,buf,bufsize)){
		infoClient(client,"URL IS TOO LONG ... \n",CONTENT_TYPE_HTML);			
	} else {
		if(FALSE == initClientMethodAndUrl(client,buf)){
			serverInternalError(client,"URL IS TOO SHORT OR YOUR METHOD NOT FOUND ");
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

// 假如其中包含.. ， 认为URL 非法
int handlePathPermission(NClient *client){
	if(strstr(client->requestUrl,"..") != NULL) {
		serverInternalError(client,"<p>YOUR URL CONTAINS SPECIAL CHARACTERS</p>");	
		return HANDLED;
	}
	return CONTINUE;
}

int handleFilePermission(NClient *client){
	char *url = client->requestUrl;
	char *url_end_pos = url + strlen(url), *file_ext_pos  = url_end_pos;
	char file_name[64] = {'\0'};
	int file_name_len = 0;
	char *allowExt[] = {"txt","html","css","js","cgi",NULL};
	char **allowPos = allowExt;
	BOOL urlAllow = FALSE;

	while(*url_end_pos != '/') {
		url_end_pos--;	
		if(*url_end_pos == '.'){
			file_ext_pos = url_end_pos + 1;	
		}
	}

	strcpy(client->filetype,file_ext_pos);

	if(*file_ext_pos == '\0') {
		client->isCgi = FALSE;
		return CONTINUE;	
	}

	while(*allowPos!= NULL){
		if(strcasecmp(*allowPos,file_ext_pos) == 0 ) {
			urlAllow = TRUE;
			break;
		}
		allowPos++;
	}

	printfRed(".....  NOT FOUND .............\n");

	if(strcasecmp("cgi",file_ext_pos) == 0 ) {
		client->isCgi = TRUE;	
	} else {
		client->isCgi = FALSE;	
	}

	if(urlAllow == FALSE) {
		serverInternalError(client,"<p>You can't request this type of file ! </p>\n");
		return HANDLED;
	}

	url_end_pos++;
	strcpy(file_name,url_end_pos);
	file_name_len = strlen(file_name);
	if(file_name_len > 0 && file_name[0] == '.') {
		serverInternalError(client,"<p>You can't request this file ! </p>\n");
		return HANDLED;
	}
	return CONTINUE;
}

int handleBySendFileContent(NClient *client){
	char **contentList = (char**)malloc(sizeof(char*) * 64);
	char **listPos = contentList;
	FILE *fp;
	char *file_path = client->realFilePath;

	//不处理目录内容和cgi请求
	if(TRUE == isPathDir(file_path) || client->isCgi == TRUE) {
		free(contentList);
		return CONTINUE;	
	}

	LOG("FOPEN THIS FILE : %s\n",file_path);
	fp = fopen(file_path,"r");

	if(fp <= 0) {
		fclose(fp);
		return CONTINUE;	
	}

	while(!feof(fp)) {
		*listPos = (char*) malloc(sizeof(char) * 128);
		bzero(*listPos,128);
		fread(*listPos,127,1,fp);
		listPos++;
	}
	fclose(fp);
	*listPos = NULL;

	infoClientList(client,contentList,CONTENT_TYPE_HTML);
	return HANDLED;
}

int handlePostData(NClient* client) {
	char line[256] = {'\0'};
	char *lengthPos;
	int contentLength;
	if(client->rt != POST) {
		return CONTINUE;
	}
	do {
		readLine(client,line,256);
		if(strncasecmp("Content-Length",line,14) == 0) {
			lengthPos = line + 14;
			while(*lengthPos++ != ':') ;
			contentLength = atoi(lengthPos); 
		}
		if(0 == strcmp(line,"\r\n")){
			client->postData = (char*)malloc(sizeof(char) * ( contentLength + 1));
			readSize(client,client->postData,contentLength);
			client->postData[contentLength] = '\0';
			break;	
		}
	} while(1);
	return CONTINUE;
}

int cgiRequest(NClient* client) {
	char response[Config.MaxResponseLen];
	bzero(response,Config.MaxResponseLen);
	if (client->isCgi == TRUE) {
		if( TRUE == doMyCgiRequest(client,response,Config.MaxResponseLen) ){
			infoClient(client,response,CONTENT_TYPE_HTML);
		} else {
			// ERROR 出错了	
		}
		return HANDLED;	
	}
	return CONTINUE;
}

void infoClientList(NClient *client,char** messageList,char* contentType) {
	char **scanPos = messageList;
	char text[Config.MaxResponseLen] ;
	int messageLength = 0;
	char *messageTpl = "HTTP/1.1 200 OK\r\n\
Server: myhttp\r\n\
Connection: closed\r\n\
Content-Type: %s\r\n\
Content-Length: %d \r\n\
\r\n";

    bzero(text,Config.MaxResponseLen);

	do {
		messageLength += strlen(*scanPos);	
		scanPos++;
	} while(*scanPos != NULL);

	scanPos = messageList;
	sprintf(text,messageTpl,contentType,messageLength);

	do {
		strcat(text,*scanPos); 
		scanPos++;
	} while(*scanPos != NULL);

	writeData(client,text,strlen(text));

// 在linux centos7 上运行，收不到内容的响应，暂时改成一次性发送内容
//	do {
//		writeData(client,*scanPos,strlen(*scanPos));
//		scanPos++;
//	} while(*scanPos != NULL);

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
		char *notFindMessage = "<h1>Sorry I can't find your file . </h1>\n";
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

void serverInternalError(NClient *client,char* errorMessage) {
		char *noPermissonMessage = "<h1>Sorry You have no permission ! </h1>\n";
		char text[2048] = {'\0'};
		char *messageTpl = "HTTP/1.1 500 SERVER ERROR\r\n\
Server: myhttp\r\n\
Content-Type: %s \r\n\
Content-Length: %d \r\n\
Connection: closed \r\n\
\r\n\
%s%s";
		sprintf(text,messageTpl,CONTENT_TYPE_HTML,strlen(errorMessage) + strlen(noPermissonMessage) ,noPermissonMessage,errorMessage);
		writeData(client,text,strlen(text));
}

BOOL isPathDir(char *path) {
	struct stat info;
	stat(path,&info);
	if(S_ISDIR(info.st_mode)){
		return TRUE;
	} else {
		return FALSE;
	}
}
