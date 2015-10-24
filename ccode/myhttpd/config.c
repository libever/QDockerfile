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
}

static void configLine(char *line){
	if(strlen(line) == 0 || line[0] == '\0' || line[0] == '#') {
			return;	
	}
	LOG(line);
}

static void configReadLine(FILE **fpp,char *buf, int size) {
	FILE *fp = *fpp;
	char c = '\0';
	int rlen = 0;
	BOOL dbegin = FALSE;
	for ( ; rlen < size ; rlen++){
		c = fgetc(fp);

		if(c == -1) {
			buf[rlen] = '\0';
			return;
		}

		//忽略之前的空格
		if (cblank(c) && dbegin == FALSE) {
				rlen = 0;
		//数据开始之前遇到#字符
		} else if ( c == '#' && dbegin == FALSE) {
				rlen = 0;
		} else if ( c == '\n' && dbegin == TRUE) {
				buf[rlen] = '\0';
				return;
		} else if (!cblank(c) && dbegin == FALSE) {
				dbegin = TRUE;	
				buf[rlen] = c;
		//数据开始以后遇到空字符
		} else if (cblank(c) && dbegin == TRUE) {
				buf[rlen] = c;
		} else {
				buf[rlen] = c;
		}
	}
	/*ExitMessage("Your Config Line Is Too Long!\n");*/
}
