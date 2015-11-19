#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <execinfo.h>


void handler(int sig) {
	int fd = open("/tmp/segv.out",O_WRONLY | O_CREAT , S_IRWXU | S_IRGRP  );
  void *array[10];
  int size;
  size = backtrace(array, 10);
  fprintf( stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, fd);
	close(fd);
  exit(1);
}

static __attribute__((constructor)) void init() {
    signal(SIGSEGV, handler);    
}

