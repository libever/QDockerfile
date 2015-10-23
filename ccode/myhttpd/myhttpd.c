#include "myhttpd.h"
#include "common.h"
#include "net.h"
#include "config.h"
#include "handler.h"

void StopServer(){
	closeServer(myServer);
}

int main(int argc, char** argv){
	int port = 1028;
	int process_born = 5;
	char document_root[128] = "/Users/xingyue/outcode/git/lovely-codes/QDockerfile/ccode/myhttpd/html";
	char *configFile = "./etc/myhttpd.conf";

	if(argc == 2) {
		configFile = argv[1];	
	}

	initConfig(configFile);
	myServer = initNServer(port,process_born,document_root);
	signal(SIGINT, StopServer); 
	LOG("INIT server AT %d \n",port);
	openServer(myServer);
	loopServer(myServer,loopMainHandler);
	StopServer();
	return 0;
}
