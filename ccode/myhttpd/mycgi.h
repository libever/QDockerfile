#ifndef MYHTTPD_MYCGI_H
#define MYHTTPD_MYCGI_H

#include "common.h"
#include "net.h"
#include "handler.h"
#include "react.h"

BOOL doMyCgiRequest(NClient *client,char* response,int max_len);

#endif
