#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>

void run_so_file(char* so_name,char* so_entry,int argc,char** argv);
void printfRed(char *format,...);

int main(int argc, char** argv){
	DIR *dir = opendir(".");
	struct dirent *dirent;
	char *soend;
	char *so_entry;

	if(argc >=2) {
		so_entry = argv[1];
	} else {
		so_entry = "so_main";	
	}

	while((dirent = readdir(dir)) != NULL){
		if(strlen(dirent->d_name) >= 3) {
			soend = dirent->d_name + strlen(dirent->d_name) - 3;
			if(strcmp(soend,".so") == 0){
				run_so_file(dirent->d_name,so_entry,argc,argv);
			}
		}
	}
	closedir(dir);
	return 0;
}

void run_so_file(char* so_name,char* so_entry,int argc,char** argv){
	void *sofp;
	void (*funfp)(int,char**);
	printf("RUN MODULE : %s.so\n",so_name);
	sofp = dlopen(so_name,RTLD_NOW);
	if(sofp != NULL) {
		funfp = dlsym(sofp,so_entry);
		if(funfp == NULL) {
			printfRed("%s.so HAS NO SO_ENTRY : %s \n",so_name,so_entry);
		} else {
			funfp(argc,argv);
		}
	} else {
		printfRed("LOAD FAILED : %s.so\n",so_name);
	}
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

