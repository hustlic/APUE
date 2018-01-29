#include "ourhdr.h"

#define BUFFSIZE 1024

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    //read from fd to buf
    while( (n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0 )
    {
        //write buf to fd
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_quit("write error\n");
        }
    }

    if (n < 0)
    {
        err_quit("read error\n");
    }

    exit(0);
}