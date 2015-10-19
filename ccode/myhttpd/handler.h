#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include <pthread.h>
#include <sys/wait.h>

void loopMainHandler(NServer *);
void handlerGetRequest(NServer *);
void handlerPostRequest(NServer *);
void cgiRequest(NServer *);

#endif
