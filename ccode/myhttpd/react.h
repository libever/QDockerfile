#ifndef MYHTTPD_REACT_H
#define MYHTTPD_REACT_H

#include "net.h"

#define HANDLED 1
#define CONTINUE 2 

#define CONTENT_TYPE_HTML "text/html"
void infoClient(NClient *,char*,char*);
void infoClientList(NClient *,char**,int[],char*);
void cgiContent(NClient *,char*);
void serverInternalError(NClient *,char*);

#endif
