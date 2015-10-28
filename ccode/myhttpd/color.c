#include "color.h"

void printfGreen(char *message){
	printf("\033[0;32m%s\033[0;0m",message);
}

void printfRed(char *message){
	printf("\033[0;31m%s\033[0;0m",message);
}
