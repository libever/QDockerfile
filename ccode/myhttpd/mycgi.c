#include "mycgi.h"

BOOL doMyCgiRequest(NClient *client,char* response,int max_len){
	strcpy(response,"Hello I am cgi request ");
	return TRUE;
}
