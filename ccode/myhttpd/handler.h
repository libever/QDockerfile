#ifndef MYHTTPD_HANDLER_H
#define MYHTTPD_HANDLER_H

#include "net.h"
#include "common.h"
#include "config.h"
#include "mycgi.h"
#include "module.h"
#include "react.h"

#include <pthread.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>

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
int handleBySoModule(NClient *);

void* loopRequest(void *);
char* fileExt(char*);
BOOL isPathDir(char *path);

#endif
