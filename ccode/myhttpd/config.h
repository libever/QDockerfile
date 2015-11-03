#ifndef MYHTTPD_CONFIG_H
#define MYHTTPD_CONFIG_H

#include "common.h"

typedef struct {
	int ProcessBorn;
	BOOL DEBUG;
	BOOL NOTHREAD;
	int Port;
	int MaxResponseLen;
	char DocumentRoot[128];
	int MaxBlocks;
	int BlockSize;
	char LogPath[128];
	char ModulePath[128];
	char LoadModules[512];
	int MaxLogSize;
} ConfigT;

typedef struct {
	char *configName;
	void (*configFun)(char* value);
} ConfigEntry;

ConfigT Config;

void initConfig(char *);
void configLine(char*);
void configReadLine(FILE **,char*,int);

#define CONFIG_ENTRY_ITEM(CONFIG_NAME) {#CONFIG_NAME,config##CONFIG_NAME}

#define CONFIG_FUN_NAME_DEFINE(CONFIG_NAME) void config##CONFIG_NAME(char *value);

CONFIG_FUN_NAME_DEFINE(ProcessBorn)
CONFIG_FUN_NAME_DEFINE(Port)
CONFIG_FUN_NAME_DEFINE(DEBUG)
CONFIG_FUN_NAME_DEFINE(DocumentRoot)
CONFIG_FUN_NAME_DEFINE(MaxResponseLen)
CONFIG_FUN_NAME_DEFINE(BlockSize)
CONFIG_FUN_NAME_DEFINE(MaxBlocks)
CONFIG_FUN_NAME_DEFINE(NOTHREAD)
CONFIG_FUN_NAME_DEFINE(LogPath)
CONFIG_FUN_NAME_DEFINE(ModulePath)
CONFIG_FUN_NAME_DEFINE(LoadModules)
CONFIG_FUN_NAME_DEFINE(MaxLogSize)

#define CONFIG_INT_FUN(CONFIG_NAME) void config##CONFIG_NAME(char *value) {Config.CONFIG_NAME = atoi(value);}
#define CONFIG_STR_FUN(CONFIG_NAME) void config##CONFIG_NAME(char *value) {strcpy(Config.CONFIG_NAME,value);}
#define CONFIG_BOOL_FUN(CONFIG_NAME) void config##CONFIG_NAME(char *value) { Config.CONFIG_NAME = strncasecmp(value,"TRUE",4) == 0 ? TRUE : FALSE ;}

#endif
