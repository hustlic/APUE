/**
* 创建2个进程，父进程向子进程写内容，通过管道
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

int main(int argc, char *argv[])
{
    int pipe_fd[2], n = -1;
    pid_t pid;
    char buf[MAX_LINE]={0};
    
    if(pipe(pipe_fd) < 0)
    {
        printf("Failed to pipe\n");
        return -1;
    }

    if((pid = fork()) < 0)
    {
        printf("Failed to fork\n");
        return -1;
    }

    if(pid == 0)
    {
        //child, close write pipe
        close(pipe_fd[1]);
        n = read(pipe_fd[0], buf, MAX_LINE);
        write(STDOUT_FILENO, buf, n);
        write(STDOUT_FILENO,"\n",1);
    }
    else
    {
        //father, close read pipe
        close(pipe_fd[0]);
        write(pipe_fd[1],"send by child", strlen("send by child"));
    }

    exit(0);
}
