#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

void run_so_file(char* so_name,char* so_entry,int argc,char** argv);
void printfRed(char *format,...);

int main(int argc, char** argv){
	printfRed("%s\n");
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
			printf("%s.so HAS NO SO_ENTRY : %s \n",so_name,so_entry);
		} else {
			funfp(argc,argv);
		}
	} else {
		printf("LOAD FAILED : %s.so\n",so_name);
	}
}

void printfRed(char *format,...){
	printf("\033[0;31m");
	printf("Hello I am red ");
	/*printf("%s\033[0;0m",message);*/
	printf("\033[0;0m");
}

