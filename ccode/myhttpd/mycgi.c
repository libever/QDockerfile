#include "mycgi.h"
#include "handler.h"

BOOL doMyCgiRequest(NClient *client,char* response,int max_len){
	int cgi_out[2],cgi_input[2];
	if (pipe(cgi_out) < 0) {
		serverInternalError(client,"PIPE ERROR ....");	
		return FALSE;
	}
	if (pipe(cgi_input) < 0) {
		serverInternalError(client,"PIPE ERROR ....");	
		return FALSE;
	}

	strcpy(response,"HELLO CGI REQUEST \n");

	return TRUE;
}
