#include "../net.h"
#include "../module.h"

void handler(NClient *client){
	printf("\n......................................MY MODULE \n ");
}

module_t* init_module(){
	module_t *m = (module_t *) malloc(sizeof(module_t));
	m->handler = handler;
	return m;
}
