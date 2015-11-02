#ifndef MYHTTPD_H
#define MYHTTPD_H

#include "module.h"
#include "net.h"
#include "common.h"
#include "config.h"
#include "handler.h"

#include <signal.h>
static NServer *myServer;
module_list *mlist;

void StopServer();

#endif
