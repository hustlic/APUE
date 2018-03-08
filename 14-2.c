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
#include <string.h>

#define DEF_PAGER "/bin/more"
#define MAX_LINE 1024

int main(int argc, char *argv[])
{
    int n; //每次写入管道的字节数
    int fd[2]; //管道fd
    pid_t pid; // 保存子进程id
    FILE *fp = NULL;
    int i = 0;    
    char *pager; 
    char *argv0;
    
    char buf[1024]={0};
    
    if((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("failed to open %s\n", argv[0]);
        return -1;
    }

    if(pipe(fd) < 0)
    {
        printf("failed to create pipe\n");
        fclose(fp);
        return -1;
    }
    
    if((pid = fork()) < 0)
    {
        printf("failed to fork\n");
        fclose(fp);
        close(fd[0]);
        close(fd[1]);
        return -1;
    }

    if(pid > 0)
    {
        //父进程, 读取文件，将内容写入到管道
        close(fd[0]);
        while(fgets(buf, MAX_LINE, fp) != NULL)
        {
            n = strlen(buf);
            if(write(fd[1],buf,n) != n )
            {
                printf("error while writing to fd[1]\n");
            }
            memset(buf,0,sizeof(buf));
        }
        close(fd[1]);

        if(waitpid(pid, NULL, 0) < 0)
        {
            printf("waitpid error\n");
        }

        exit(0);
            
         
        
    }
    else
    {
        //子进程
        close(fd[1]);
        if(fd[0] != STDIN_FILENO)
        {
            if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
            {
                printf("failed to dup fd[0] to stdin");
            }
            close(fd[0]);
        }

        if((pager=getenv("PAGER")) == NULL)
        {
            pager = DEF_PAGER;
        }

        if( (argv0 = strrchr(pager, '/')) != NULL )
        {
             argv0++;
        }
        else
        {
            argv0 = pager;
        }

        if(execl(pager, argv0, (char*)0) < 0)
        {
            printf("failed to execl\n");
            return -1;
        }
        
    }

}



