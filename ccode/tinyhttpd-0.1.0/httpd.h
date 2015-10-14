#ifndef HTTPD_COMMON_STRING_H
#define HTTPD_COMMON_STRING_H


#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define BADSTRING "HTTP/1.0 400 BAD REQUEST\r\n\
Server: jdbhttpd/0.1.0\r\n\
Content-type: text/html\r\n\
\r\n\
<P>Your browser sent a bad request,uch as a POST without a Content-Length.\r\n"

#define INTERNAL_SERVER_ERROR_STRING "HTTP/1.0 500 Internal Server Error\r\n\
Server: jdbhttpd/0.1.0\r\n\
Content-type: text/html\r\n\
\r\n\
<P>Error prohibited CGI execution.\r\n"


#define METHOD_NOT_FOUND_STRING "HTTP/1.0 501 Method Not Implemented\r\n\
Server: jdbhttpd/0.1.0\r\n\
Content-Type: text/html\r\n\
\r\n\
<HTML><HEAD><TITLE>Method Not Implemented\r\n\
</TITLE></HEAD>\r\n\
<BODY><P>HTTP request method not supported.\r\n\
</BODY></HTML>\r\n"

#define NOT_FOUND_STRING "HTTP/1.0 404 NOT FOUND\r\n\
Server: jdbhttpd/0.1.0\r\n\
Content-Type: text/html\r\n\
\r\n\
<HTML><TITLE>Not Found</TITLE>\r\n\
<BODY><P>The server could not fulfill\r\n\
your request because the resource specified\r\n\
is unavailable or nonexistent.\r\n\
</BODY></HTML>\r\n"

static int server_socket;

#define ISspace(x) isspace((int)(x))
void accept_request(int*);
void bad_request(int);
void cat(int, FILE *);
void cannot_execute(int);
void error_die(const char *);
void execute_cgi(int, const char *, const char *, const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
int startup(u_short *);
void unimplemented(int);
void StopServer();



#endif
