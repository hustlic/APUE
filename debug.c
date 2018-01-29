#include "ourhdr.h"

void err_quit(const char *fmt, ...)
{
    va_list args; 
    char buf[1000];
    va_start(args, fmt);
    vsnprintf((char *)buf, 1000, (char *)fmt, args);
    va_end(args);
    printf("%s\n", buf);
    exit(-1);
}

void err_info(const char *fmt, ...)
{
    va_list args; 
    char buf[1000];
    va_start(args, fmt);
    vsnprintf((char *)buf, 1000, (char *)fmt, args);
    va_end(args);
    printf("%s\n", buf);    
}

void err_sys(const char *fmt, ...)
{
    va_list args; 
    char buf[1000];
    va_start(args, fmt);
    vsnprintf((char *)buf, 1000, (char *)fmt, args);
    va_end(args);
    printf("%s\n", buf);
    exit(-1);
}