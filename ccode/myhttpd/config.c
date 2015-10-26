#include "common.h"
#include "config.h"

void initConfig(char *fileName) {
	FILE *fp = fopen(fileName,"r");
	int max_line_len = 128;
	char line[max_line_len];

	if ( 0 == fp) {
		ExitMessage("Config File Not Found ... \n");	
	}

	printf("init myhttpd config from file : %s \n",fileName);
	while(!feof(fp)) {
		configReadLine(&fp,line,max_line_len);	
		configLine(line);
	}

	fclose(fp);

}

void configLine(char *line){

	char *configName = line;
	char *configValue =  line;

	if(strlen(line) == 0 || line[0] == '\0' || line[0] == '#') {
			return;	
	}

	printf("%s\n",line);

	while(*configValue != ' ') {
		configValue++;	
	}

	*configValue = '\0';
	configValue++;
	
	ConfigEntry entryList[] = {
		{"PROCESS_BORN",configProcessBorn},
		{"DEBUG",configDEBUG},
		{"PORT",configPort},
		{"DOCUMENT_ROOT",configDocumentRoot},
		{NULL,NULL}
	};

	ConfigEntry *scanPos = entryList;

	while(scanPos->configName != NULL) {
		if(strcmp(configName,scanPos->configName) == 0) {
			return scanPos->configFun(configValue);	
		}
		scanPos++;
	}

}

void configReadLine(FILE **fpp,char *buf, int size) {
	char tmp_line[size] ;
	char *pos = tmp_line;
	FILE *fp = *fpp;
	char c = '\0';
	int rlen = 0;
	bzero(buf,size);
	bzero(tmp_line,size);
	for ( ; rlen < size ; rlen++){
		c = fgetc(fp);
		if(c == -1) {
			buf[rlen] = '\0';
			return;
		}
		if( c == '\n') {
			tmp_line[rlen] = '\0';
			break;	
		} else {
			tmp_line[rlen] = c ;
		}
	}

	if(strlen(tmp_line) >= (size_t)size) {
		ExitMessage("Your Config Line Is Too Long!\n");
	}

	do {
		//所有的都是空字符，那么直接返回空行
		if(*pos == '\0') {
			buf[0] = '\0';	
			return;
		}
		if( cblank(*pos)){
				pos++	;
		} else {
			break;	
		}
	} while(1);

	strcpy(buf,tmp_line);
}

void configProcessBorn(char *value) { 
	Config.ProcessBorn = atoi(value);
}

void configDEBUG(char *value) { 
	Config.DEBUG = strcasecmp(value,"TRUE") == 0 ? TRUE : FALSE;
}

void configPort(char *value) { 
	Config.PORT= atoi(value);
}

void configDocumentRoot(char *value){
	strcpy(Config.DocumentRoot,value);
}
