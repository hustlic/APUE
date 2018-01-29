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

    char buf[20]={0};
    int cnt = 0;
    
    fd = open(TEST_FILE,O_RDWR|O_CREAT|O_SYNC);

    if (fd < 0 )
    {
        err_quit("failed to open %s, %s\n",TEST_FILE, strerror(errno));
    }

    offset = lseek(fd, 0, SEEK_SET);
    printf("current offset is %d\n", offset);

    offset = lseek(fd, -strlen(TEST_STRING), SEEK_SET);
    printf("current offset is %d\n", offset);

    while(1)
    {
        snprintf(buf,sizeof(buf), TEST_STRING" %d\n", cnt++);

        offset = lseek(fd, 0, SEEK_CUR);
        printf("before write new offset is %d\n", offset);
        ret = write(fd, buf, strlen(buf));

        offset = lseek(fd, 0, SEEK_CUR);
        printf("after write new offset is %d\n\n\n", offset);
        sleep(2);
    }
    
    close(fd);
}

