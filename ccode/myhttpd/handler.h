#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include <pthread.h>
#include <sys/wait.h>

void loopMainHandler(NServer *);
void handlerGetRequest(NClient *);
void handlerPostRequest(NClient *);
void cgiRequest(NClient *);
void infoClient(NClient *,char*);

#endif
