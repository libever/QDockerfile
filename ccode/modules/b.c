#include <stdio.h>
#include <dlfcn.h>


void run_in_so(char* f,char* m){
	void *sofp;
	void (*funfp)();
	printf("RUN MODULE : %s.so\n",f);
	sofp = dlopen(f,RTLD_NOW);
	funfp = dlsym(sofp,"func");
	funfp(m);
}

int main(){

	char *module_name[] = {
		"m1.so","m2.so",NULL
	};

	char **p = module_name;

	while(*p != NULL) {
		run_in_so(*p,*p);
		p++;

	}

	return 0;
}
