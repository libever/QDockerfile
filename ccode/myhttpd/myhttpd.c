#include "myhttpd.h"
#include "common.h"
#include "net.h"
#include "handler.h"

void StopServer(){
	closeServer(myServer);
}

int main(){
	int port = 1028;
	int process_born = 1;
	char document_root[10] = ".";
	myServer = initNServer(port,process_born,document_root);
	signal(SIGINT, StopServer); 
	printf("INIT server at %d \n",port);
	openServer(myServer);
	loopServer(myServer,loopMainHandler);
	StopServer();
	return 0;
}
