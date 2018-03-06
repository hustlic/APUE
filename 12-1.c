/**
* 
*/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_SIZE 1000*10
char buf[MAX_SIZE];

void set_fl(int fd, int flag);
void clr_fl(int fd, int flag);

int main(int argc, char *argv[])
{
    int ntowrite, nwrite;
    char *ptr;

    //从标准输入读取内容
    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes \n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);

    for(ptr = buf; ntowrite > 0;)
    {
        nwrite = write(STDOUT_FILENO,buf,ntowrite);
        if(nwrite > 0)
        {
            fprintf(stderr, "write %d bytes\n", nwrite);
            ntowrite -= nwrite;
            ptr += nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);

    exit(0);
    
}


void set_fl(int fd, int flag)
{
   int  val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        printf("fcntl F_GETFL error");

    val |= flag;        /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0)
        printf("fcntl F_SETFL error");
}

void clr_fl(int fd, int flag)
{
   int  val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        printf("fcntl F_GETFL error");

    val &= ~flag;        /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0)
        printf("fcntl F_SETFL error");
}

