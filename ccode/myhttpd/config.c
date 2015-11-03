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

	while(*configValue != ' ') {
		configValue++;	
	}

	*configValue = '\0';
	configValue++;

	printf("%s:%s\n",configName,configValue);
	
	ConfigEntry entryList[] = {
		CONFIG_ENTRY_ITEM(DEBUG),
		CONFIG_ENTRY_ITEM(Port),
		CONFIG_ENTRY_ITEM(ProcessBorn),
		CONFIG_ENTRY_ITEM(DocumentRoot),
		CONFIG_ENTRY_ITEM(MaxResponseLen),
		CONFIG_ENTRY_ITEM(MaxBlocks),
		CONFIG_ENTRY_ITEM(BlockSize),
		CONFIG_ENTRY_ITEM(NOTHREAD),
		CONFIG_ENTRY_ITEM(LogPath),
		CONFIG_ENTRY_ITEM(ModulePath),
		CONFIG_ENTRY_ITEM(LoadModules),
		CONFIG_ENTRY_ITEM(MaxLogSize),
		{NULL,NULL}
	};

	ConfigEntry *scanPos = entryList;

	while(scanPos->configName != NULL) {
		//printf("%s >>>>>>>>>> %s\n",configName,scanPos->configName);
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


//整形配置函数
CONFIG_INT_FUN(MaxLogSize)
CONFIG_INT_FUN(ProcessBorn)
CONFIG_INT_FUN(Port)
CONFIG_INT_FUN(MaxResponseLen)
CONFIG_INT_FUN(BlockSize)
CONFIG_INT_FUN(MaxBlocks)

//布尔配置函数
CONFIG_BOOL_FUN(DEBUG)
CONFIG_BOOL_FUN(NOTHREAD)

//字符串配置函数
CONFIG_STR_FUN(DocumentRoot);
CONFIG_STR_FUN(LogPath);
CONFIG_STR_FUN(ModulePath);
CONFIG_STR_FUN(LoadModules);
