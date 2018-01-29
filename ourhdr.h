#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <stdarg.h>

#include <dirent.h>

#include <errno.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>


#define DEBUG(...)\
do{\
    fprintf(stderr,"Func=%s(),Line=%d, ",__func__,__LINE__);\
    fprintf(stderr,__VA_ARGS__);\
}while(0)

void err_info(const char *fmt, ...);

void err_quit(const char *fmt, ...);

void err_sys(const char *fmt, ...);