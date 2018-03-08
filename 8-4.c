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

#define PAGER "/bin/more"

int main(int argc, char *argv[])
{
    int n; //ÿ��д��ܵ����ֽ���
    int fd[2]; //�ܵ�fd
    pid_t pid; // �����ӽ���id
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
        //������
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
        //�ӽ���
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



