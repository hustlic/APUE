#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>        
        
char buf[] = "This is buf\n";

int global = 99;

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    int var = 88;
    
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
    {
        printf("Write error, %s\n", strerror(errno));
    }

    printf("Before vfork\n");

    pid = vfork();

    if(pid == 0)
    {
        //child process
        global++;
        var++;
        exit(0);   
    }
    else if(pid > 0)
    {
        //father process, sleep to make sure child run first
        //sleep(3);
    }
    else
    {
        //error
    }

    printf("pid=%d, global=%d, var=%d\n", getpid(), global, var);
    exit(0);

}
