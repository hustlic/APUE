/**
* ����1���ܵ�
* �ӽ��̵ı�׼�����Ϊ�ܵ��Ķ��ˣ� 
* �����̶�ȡ�ļ���������д��ܵ�
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
    int n; //ÿ��д��ܵ����ֽ���
    int fd[2]; //�ܵ�fd
    pid_t pid; // �����ӽ���id
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
        //������, ��ȡ�ļ���������д�뵽�ܵ�
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
        //�ӽ���
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



