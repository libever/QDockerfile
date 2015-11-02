#ifndef MYHTTPD_H
#define MYHTTPD_H

#include <signal.h>
#include "module.h"
#include "net.h"
static NServer *myServer;
module_list *mlist;

void StopServer();

#endif
