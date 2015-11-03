#include <react.h>
/*#include "../net.h"*/
#include <module.h>

int handler(NClient *client){
	return CONTINUE;
	/*infoClient(client,"<h1>OK ..... Hello world</h1>",CONTENT_TYPE_HTML);*/
	/*return HANDLED;*/
}

void serverHandler(NServer *server){
	printf("run at server .... \n");
}

module_t* init_module(){
	module_t *m = (module_t *) malloc(sizeof(module_t));
	m->handler = handler;
	m->serverHandler = serverHandler;
	return m;
}
