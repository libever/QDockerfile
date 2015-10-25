#include "common.h"
#include "config.h"

void initConfig(char *fileName) {
	FILE *fp = fopen(fileName,"r");
	int max_line_len = 128;
	char line[max_line_len];

	if ( 0 == fp) {
		ExitMessage("Config File Not Found ... \n");	
	}

	while(!feof(fp)) {
		configReadLine(&fp,line,max_line_len);	
		configLine(line);
	}

	fclose(fp);

	printf("%d\n",Config.ProcessBorn);

}

static void configLine(char *line){

	char *configName = line;
	char *configValue =  line;

	if(strlen(line) == 0 || line[0] == '\0' || line[0] == '#') {
			return;	
	}

	while(*configValue != ' ') {
		configValue++;	
	}

	*configValue = '\0';
	configValue++;
	
	printf("%s|=>|%s \n",configName,configValue);
	ConfigEntry entryList[] = {
		{"ProcessBorn",configProcessBorn},
		{NULL,NULL}
	};

	ConfigEntry *scanPos = entryList;

	while(scanPos->configName != NULL) {
		if(strstr(configName,scanPos->configName) != NULL) {
			return scanPos->configFun(configValue);	
		}
		scanPos++;
	}

}

static void configReadLine(FILE **fpp,char *buf, int size) {
	char tmp_line[size] ;
	char *pos = tmp_line;
	FILE *fp = *fpp;
	char c = '\0';
	int rlen = 0;
	BOOL dbegin = FALSE;
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

	if(strlen(tmp_line) >= size) {
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
	printf("................\n");
	Config.ProcessBorn = atoi(value);
	printf("%d\n",Config.ProcessBorn);
}

void configDEBUG(char *value) { 
	Config.DEBUG = strcasecmp(value,"TRUE") ? TRUE : FALSE;
}

