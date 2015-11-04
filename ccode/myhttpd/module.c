#include "common.h"
#include "module.h"
#include "color.h"
#include <dlfcn.h>

module_list *init_module_list(char *module_path, char *load_modules) {
	module_t* (*funfp)();
	module_list *end;
	module_list *mlist ; 
	char *module_name[10];
	char *pos = load_modules;
	int module_index = 0;
	int module_count = 0;
	BOOL line_end = FALSE;
	char so_path[128];
	void *sofp;

	if(module_path == NULL || strlen(module_path) < 2 || load_modules == NULL || strlen(load_modules) < 2) {
		return NULL;	
	}

	for(;module_index < 10; module_index++){
		module_name[module_index] = pos;
		while(!cblank(*pos)){
			if(*pos == '\0') {
				line_end = TRUE;	
				break;
			}
			pos++;	
		}
		*pos++ = '\0';
		while(cblank(*pos)){
			if(*pos == '\0') {
				line_end = TRUE;	
				break;
			}
			pos++;	
		}
		if(line_end == TRUE) break;
	}

	module_count = module_index + 1;

	for(module_index = 0 ; module_index < module_count;module_index++){
		bzero(so_path,128);
		sprintf(so_path,"%s/%s.so",module_path,module_name[module_index]);
		sofp = dlopen(so_path,RTLD_NOW);
		if(sofp != NULL) {
			funfp = dlsym(sofp,"init_module");
			if(funfp == NULL) {
				printfRed("%s.so HAS NO SO_ENTRY : %s \n",so_path,"init_module");
			} else {
                if(module_index == 0) {
                    end = (module_list*) malloc(sizeof(module_list));
                    mlist = end;            
                } else {
                    end->next = (module_list*) malloc(sizeof(module_list)); 
                    end = end->next;
                }
				end->module = funfp();
			}
		} else {
			printfRed("LOAD FAILED : %s \n",so_path);
		}
	}

	end = NULL;

	return mlist;
}
