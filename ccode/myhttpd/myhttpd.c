#include "myhttpd.h"

void StopServer(){
	closeServer(myServer);
}

int main(int argc, char** argv){

	char *configFile = "./etc/myhttpd.conf";
	if(argc == 2) {
		configFile = argv[1];	
	}
	printfGreen(">>>>>>>>>>>>>>>>>>>>>>>>>>>>    <<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\n");
	initConfig(configFile);
	myServer = initNServer(Config.PORT,Config.ProcessBorn,Config.DocumentRoot);
	mlist = init_module_list(Config.ModulePath,Config.LoadModules);
	signal(SIGINT, StopServer); 
	openServer(myServer);
	loopServer(myServer,loopMainHandler);
	StopServer();
	return 0;
}
