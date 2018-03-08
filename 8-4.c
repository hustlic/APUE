/**
* 创建1个管道
* 子进程的标准输入成为管道的读端， 
* 父进程读取文件，将内容写入管道
* 
*/


#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGER "/bin/more"

int main(int argc, char *argv[])
{
    int n; //每次写入管道的字节数
    int fd[2]; //管道fd
    pid_t pid; // 保存子进程id
    FILE *fp = NULL;
    int i = 0;

    if((fp = fopen(argv[1], "w+")) == NULL)
    {
        printf("failed to open %s\n", argv[0]);
        return -1;
    }
    
    if((pid = fork()) < 0)
    {
        printf("failed to fork\n");
        return -1;
    }

    if(pid > 0)
    {
        //父进程
        while(i < 10)
        {
            fputs("father writing...\n", fp);
            printf("father writing...\n");
            i++;
            sleep(1);
        }
        fclose(fp);
        waitpid(pid, NULL, 0);
        
    }
    else
    {
        //子进程
        while(i < 10)
        {
            fputs("child writing...\n", fp);
            printf("child writing...\n");            
            i++;
            sleep(2);
        }
        fclose(fp);
        
    }

}



