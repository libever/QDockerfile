#include "react.h"

void infoClientList(NClient *client,char** messageList,int sizeList[],char* contentType) {
	char **scanPos = messageList;
	char *text = (char*) malloc(Config.MaxResponseLen * sizeof(char));
	int messageLength = 0;
	char *messageTpl = "HTTP/1.1 200 OK\r\n\
Server: myhttp\r\n\
Connection: closed\r\n\
Content-Type: %s\r\n\
Content-Length: %d \r\n\
\r\n";
	char *endpos ;
	bzero(text,Config.MaxResponseLen);
	do {
		messageLength += sizeList[scanPos - messageList];	
		scanPos++;
	} while(*scanPos != NULL);

	scanPos = messageList;
	sprintf(text,messageTpl,contentType,messageLength);
	endpos = text + strlen(text);

	do {
		memcpy(endpos, *scanPos,sizeList[scanPos - messageList]);
		endpos += sizeList[scanPos - messageList];
		scanPos++;
	} while(*scanPos != NULL);

	writeData(client,text,endpos - text);

	// 在linux centos7 上运行，收不到内容的响应，暂时改成一次性发送内容
	//	do {
	//		writeData(client,*scanPos,strlen(*scanPos));
	//		scanPos++;
	//	} while(*scanPos != NULL);

	//清理之前malloc的内容资源	
	scanPos = messageList;
	do {
		free(*scanPos);
		*scanPos = NULL;
		scanPos++;
	} while(*scanPos != NULL);
	free(messageList);
	messageList = NULL;

	free(text);
	text = NULL;
}

//信息量较少
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

void cgiContent(NClient *client,char* buffer) {
	char *text = (char*)malloc(sizeof(char) * Config.MaxResponseLen) ;
	bzero(text,Config.MaxResponseLen);
	char *tpl = "HTTP/1.1 200 OK\r\n%s";
	sprintf(text,tpl,buffer);
	writeData(client,text,strlen(text));
	free(text);
}
