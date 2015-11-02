#ifndef MYHTTPD_MODULE_H
#define MYHTTPD_MODULE_H

#include "net.h"

typedef struct {
	int (*handler)(NClient *);
} module_t;

typedef struct ori_module_list{
	module_t *module;
	struct ori_module_list *next;
} module_list;

module_list *init_module_list(char*,char*);

#endif
