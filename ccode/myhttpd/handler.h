#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include <pthread.h>
#include <sys/wait.h>

#define HANDLED 1
#define CONTINUE 2 

#define CONTENT_TYPE_HTML "text/html"

void loopMainHandler(NServer *);
int handleBySendFileContent(NClient *);
int handlerGetRequest(NClient *);
int handlerPostRequest(NClient *);
int cgiRequest(NClient *);
void infoClient(NClient *,char*,char*);
void* loopRequest(void *);
#endif
