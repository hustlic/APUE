/*
* File: 3-2.c
* Pratice: 
*        1. create an hole file
*        2. lseek to an negetive offset
*        
*
*/
#include "ourhdr.h"

#define TEST_FILE "test.txt"
#define TEST_STRING "hello files"

int main(void)
{
    int fd = -1;
    off_t offset = 0;
    int ret = -1;
    
    fd = open(TEST_FILE,O_RDWR|O_CREAT|O_TRUNC);

    if (fd < 0 )
    {
        err_quit("failed to open %s, %s\n",TEST_FILE, strerror(errno));
    }
    while(1);

    close(fd);
}