#include "color.h"
#include <stdarg.h>

void printfGreen(char *message){
	printf("\033[0;32m%s\033[0;0m",message);
}

void printfRed(char *format,...){
	char formatstr[2] = "% ";
	char *fpos = format;
	va_list arg_ptr;
	printf("\033[0;31m");
	va_start(arg_ptr,format);
	while(*fpos != '\0'){
		if(*fpos == '%') {
			fpos++;	
			formatstr[1] = *fpos;
			switch(formatstr[1]) {
				case 'd':
					printf("%d",va_arg(arg_ptr,int));
					break;
				case 's':
					printf("%s",va_arg(arg_ptr,char*));
					break;
				default:
					printfRed("FORMAT %s NOT SUPPORT",formatstr);
					return ;
			}
		} else {
			printf("%c",*fpos);
		}
		fpos++;
	}
	va_end(arg_ptr);
	printf("\033[0;0m");
}

