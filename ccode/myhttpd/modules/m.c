#include "../react.h"
#include "../net.h"
#include "../module.h"
#include "../handler.h"

int handler(NClient *client){
	infoClient(client,"<p>OK ..... Hello world</p>",CONTENT_TYPE_HTML);
	return HANDLED;
}

module_t* init_module(){
	module_t *m = (module_t *) malloc(sizeof(module_t));
	m->handler = handler;
	return m;
}
