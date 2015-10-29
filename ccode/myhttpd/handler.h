#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include <pthread.h>
#include <sys/wait.h>

#define HANDLED 1
#define CONTINUE 2 

#define CONTENT_TYPE_HTML "text/html"

typedef struct {
	char *file_ext;
	char *content_type;
} mimetype ;

void loopMainHandler(NServer *);
int handleBySendFileContent(NClient *);
int handlePostData(NClient *);
int cgiRequest(NClient *);
int notFindRequest(NClient *);
int handleFilePermission(NClient *);
int handlePathPermission(NClient *);

void infoClient(NClient *,char*,char*);
void infoClientList(NClient *,char**,char*);
void cgiContent(NClient *,char*);
void serverInternalError(NClient *,char*);
void* loopRequest(void *);
char* fileExt(char*);
BOOL isPathDir(char *path);

#endif
