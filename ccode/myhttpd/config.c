#include "config.h"
#include "common.h"

void initConfig(char *fileName) {
	FILE *fp = fopen(fileName,"r");

	if ( 0 == fp) {
		ExitMessage("Config File Not Found ... \n");	
	}

	fclose(fp);
}
