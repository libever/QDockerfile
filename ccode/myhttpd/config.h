#ifndef MYHTTPD_CONFIG_H
#define MYHTTPD_CONFIG_H

typedef struct {

} ConfigT;

extern ConfigT *Config;

void initConfig(char *);
static void configLine(char*);
static void configReadLine(FILE **,char*,int);

#endif
