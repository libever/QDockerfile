#include "mycgi.h"
#include "handler.h"

BOOL doMyCgiRequest(NClient *client,char* response,int max_len){
	int cgi_out[2],cgi_input[2];
	int cgi_pid;
	int content_pos = 0 ;
	char c;
	char queryenv[256] = {'\0'};

	if (pipe(cgi_out) < 0) {
		serverInternalError(client,"PIPE ERROR ....");	
		return FALSE;
	}
	if (pipe(cgi_input) < 0) {
		serverInternalError(client,"PIPE ERROR ....");	
		return FALSE;
	}

	cgi_pid = fork();

	if( cgi_pid == 0 ) {
		//子进程
		dup2(cgi_out[1], 1);
		dup2(cgi_input[0], 0);
		close(cgi_out[0]);
		close(cgi_input[1]);

		if(client->rt == POST) {
			putenv("REQUEST_METHOD=POST");	
		} else if( client->rt == GET) {
			putenv("REQUEST_METHOD=GET");	
			sprintf(queryenv,"QUERY_STRING=%s",client->queryString);
			putenv(queryenv);
		}
		execl(client->realFilePath,client->realFilePath,NULL);
		exit(0);
	} else {
		//主进程
		close(cgi_out[1]);
		close(cgi_input[0]);
		if( POST == client->rt ) {
			write(cgi_input[1],client->postData,strlen(client->postData));	
		}

		while(read(cgi_out[0],&c,1) && max_len-- >= 1 ) {
				response[content_pos++] = c;
		}

		close(cgi_out[0]);
		close(cgi_input[1]);
		waitpid(cgi_pid,NULL,0);
		response[content_pos] = '\0';
		return TRUE;
	}
}
