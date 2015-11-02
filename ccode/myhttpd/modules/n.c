#include "../net.h"
#include "../module.h"
#include "../handler.h"

int handler(NClient *client){
	printf("\n OTHER : ......... n.c ........MY MODULE \n");
	return CONTINUE;
}

module_t* init_module(){
	module_t *m = (module_t *) malloc(sizeof(module_t));
	m->handler = handler;
	return m;
}

