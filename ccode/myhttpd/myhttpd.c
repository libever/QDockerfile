#include "myhttpd.h"

void StopServer(){
	closeServer(myServer);
}

void RunSoServer(){
	module_list *m = mlist;
	if(mlist != NULL) {
		while ( m != NULL && m->module!= NULL ) {
			if(m->module->serverHandler != NULL) {
				m->module->serverHandler(myServer);	
			}
			m = m->next;
		}
	} 
}

int main(int argc, char** argv){

	char *configFile = "./etc/myhttpd.conf";
	if(argc == 2) {
		configFile = argv[1];	
	}
	printfGreen(">>>>>>>>>>>>>>>>>>>>>>>>>>>>    <<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\n");
	initConfig(configFile);
	myServer = initNServer(Config.Port,Config.ProcessBorn,Config.DocumentRoot);
	mlist = init_module_list(Config.ModulePath,Config.LoadModules);
	RunSoServer();
	signal(SIGINT, StopServer); 
	openServer(myServer);
	loopServer(myServer,loopMainHandler);
	StopServer();
	return 0;
}
