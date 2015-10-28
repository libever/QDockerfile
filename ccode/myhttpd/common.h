#ifndef MYHTTPD_COMMON_H
#define MYHTTPD_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "color.h"

#define ExitMessage(message) printf("%s\n",message);exit(1);
#define tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)

typedef enum BOOLEAN {TRUE,FALSE} BOOL;

#define LOG if(Config.DEBUG == TRUE) printf
#define cblank(c) ( c == ' ' || c == '\n' || c == '\r' || c == '\t')

#endif
