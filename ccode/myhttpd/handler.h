#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include <pthread.h>
#include <sys/wait.h>

#define HANDLED 1
#define FAILED 2 

void loopMainHandler(NServer *);
int handlerGetRequest(NClient *);
int handlerPostRequest(NClient *);
int cgiRequest(NClient *);
void infoClient(NClient *,char*);
void loopRequest(NClient *);
#endif
