#include "handler.h"
#include "common.h"
#include "config.h"
#include "mycgi.h"
#include "module.h"
#include "react.h"
#include <pthread.h>
#include <time.h>
#include<sys/stat.h>

extern module_list *mlist;

static pid_t currentPid;
static mimetype all_types[] = {
	{"html","text/html"},
	{"htm","text/html"},
	{"jpg","image/jpeg"},
	{"jpeg","image/jpeg"},
	{"png","image/png"},
	{"ico","image/x-icon"},
	{"css","text/css"},
	{"cgi","text/notype"},
	{"gif","image/gif"},
	{"woff","application/x-font-woff"},
	{"js","application/x-javascript"},
	{NULL,NULL}
};

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
			if(TRUE == Config.NOTHREAD) {
				loopRequest((void*)client);
			} else {
				if(pthread_create(&newthread , NULL, loopRequest, (void *) client) != 0) {
					ExitMessage("thread create failed ... ");
				}

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
					if(Config.NOTHREAD) {
						loopRequest((void*)client);
					} else {
						if(pthread_create(&newthread , NULL, loopRequest, (void *) client) != 0) {
							ExitMessage("thread create failed ... ");
						}
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
		handleBySoModule,
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

	mimetype *typepos = all_types;

	BOOL urlAllow = FALSE;

	while(*url_end_pos != '/') {
		url_end_pos--;	
		if(*url_end_pos == '.'){
			file_ext_pos = url_end_pos + 1;	
			break;
		}
	}

	strcpy(client->filetype,file_ext_pos);

	if(*file_ext_pos == '\0') {
		client->isCgi = FALSE;
		return CONTINUE;	
	}

	while(typepos->file_ext != NULL) {
		if(strcasecmp(typepos->file_ext,file_ext_pos) == 0 ) {
			urlAllow = TRUE;
			client->content_type = typepos->content_type;
			break;
		}
		typepos++;
	}

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
	char **contentList = (char**)malloc(sizeof(char*) * Config.MaxBlocks);
	int sizeList[Config.MaxBlocks];
	char **listPos = contentList;
	FILE *fp;
	char *file_path = client->realFilePath;
	int block_read = 0;
	int bytes_read = 0;

	//不处理cgi请求
	if(client->isCgi == TRUE) {
		free(contentList);
		contentList = NULL;
		return CONTINUE;	
	}

	//如果是目录，附加上index.html
	if( TRUE == isPathDir(file_path) ) {
		strcat(file_path,"index.html");	
		client->content_type = CONTENT_TYPE_HTML;
	}
	fp = fopen(file_path,"rb");

	if(fp == NULL) {
		return CONTINUE;	
	}

	while(!feof(fp)) {
		*listPos = (char*) malloc(sizeof(char) * Config.BlockSize);
		bzero(*listPos,Config.BlockSize);
		bytes_read = fread(*listPos,1,Config.BlockSize,fp);
		listPos++;
		sizeList[block_read++] = bytes_read;
	}
	fclose(fp);
	*listPos = NULL;

	infoClientList(client,contentList,sizeList,client->content_type);
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
	char *response = (char*)malloc(sizeof(char) * Config.MaxResponseLen);
	FILE *cgiFp;
	bzero(response,Config.MaxResponseLen);
	if (client->isCgi == TRUE) {
		cgiFp = fopen(client->realFilePath,"r");
		if(cgiFp == NULL) {
			free(response);
			return CONTINUE;
		}
		fclose(cgiFp);

		if( TRUE == doMyCgiRequest(client,response,Config.MaxResponseLen) ){
			cgiContent(client,response);
		} else {
			// ERROR 出错了	
		}
		free(response);
		return HANDLED;	
	}
	free(response);
	return CONTINUE;
}

//处理so模块处理
int handleBySoModule(NClient *client){
	module_list *m = mlist;
	int requestRes;
	if(mlist != NULL) {
		while ( m != NULL && m->module!= NULL && m->module->handler != NULL) {
			requestRes = m->module->handler(client);	
			switch(requestRes) {
				case HANDLED:
					return HANDLED;
					break;
				case CONTINUE:
					m = m->next;
					break;
				default :
					printfRed("YOUR RETURN INVALID \n");
					m = m->next;
					break;
			}
		}
		return requestRes;
	} else {
		return CONTINUE;	
	}
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
