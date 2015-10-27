void execute_cgi(int client, const char *path, const char *method, const char *query_string) {
	
	if (pipe(cgi_output) < 0) {
		cannot_execute(client);
		return;
	}

	if (pipe(cgi_input) < 0) {
		cannot_execute(client);
		return;
	}

	if ( (pid = fork()) < 0 ) {
		cannot_execute(client);
		return;
	}
	
	if (pid == 0) {
		dup2(cgi_output[1], 1);
		dup2(cgi_input[0], 0);
		close(cgi_output[0]);
		close(cgi_input[1]);
		sprintf(meth_env, "request_method=%s", method);
		putenv(meth_env);
		if (strcasecmp(method, "get") == 0) {
			sprintf(query_env, "query_string=%s", query_string);
			putenv(query_env);
		} else {  
			sprintf(length_env, "content_length=%d", content_length);
			putenv(length_env);
		}
		execl(path, path, null);
		exit(0);
	} else {   
		//主进程
		close(cgi_output[1]);
		close(cgi_input[0]);
		if (strcasecmp(method, "post") == 0) {
			for (i = 0; i < content_length; i++) {
				recv(client, &c, 1, 0);
				//把数据写入到子进程的标准输入
				write(cgi_input[1], &c, 1);
			}
		}
		
		//读标准输出
		while (read(cgi_output[0], &c, 1) > 0) {
			send(client, &c, 1, 0);
		}

		close(cgi_output[0]);
		close(cgi_input[1]);
		waitpid(pid, &status, 0);
	}
}

