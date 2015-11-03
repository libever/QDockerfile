#include "log.h"

void logfile(char* logfilename){
	time_t now; 
	int  daynum;
	struct tm *t;
	time(&now);
	t = localtime(&now);
	daynum = ( 1900 + t->tm_year ) * 10000  + ( t->tm_mon + 1 ) * 100 + t->tm_mday;
	sprintf(logfilename,"%s/l_%d.log",Config.LogPath,daynum);
}

int mylog(char *format,...){
	char logbuf[Config.MaxLogSize];
	char logfilename[128];
	int i=0;
	bzero(logbuf,Config.MaxLogSize);
	va_list vArgList;
	va_start (vArgList, format); 
	i = vsnprintf(logbuf, 50, format, vArgList); 
	va_end(vArgList);
	logfile(logfilename);

	FILE *fp = fopen(logfilename,"a+");
	fwrite(logbuf,strlen(logbuf),1,fp);
	fclose(fp);

	return i;
}
