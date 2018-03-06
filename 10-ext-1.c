/**
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 1024*1024*1024*1

typedef struct
{
    int age;
    int gender;
    char name[20];
    char *buf;
}student;

static void sig_usr(int signo);


int main(int argc, char *argv[])
{
    if(signal(SIGALRM, sig_usr) == SIG_ERR)
    {
        printf("Failed to register signal USR1\n");
    }

    FILE *fp = fopen("fopen.txt", "a+");
    if(!fp)
    {
        printf("Failed to create fopen.txt, %s\n",strerror(errno));
        return -1;
    }

    student stu1;

    stu1.buf = (char *)malloc(MAX_SIZE);
    
    printf("%s,%d,size=%ld\n", __FUNCTION__,__LINE__,sizeof(stu1.buf));

#if 1    
    long i = 0;
    for(; i<MAX_SIZE;i++)
    {
        stu1.buf[i] = '1';
    }
    printf("%s,%d\n", __FUNCTION__,__LINE__);
    stu1.age = 18;
    stu1.gender = 1;
    
    memcpy(stu1.name, "Lileilei", sizeof(stu1.name));

    alarm(1);
    if(fwrite((stu1.buf), MAX_SIZE, 1, fp) != 1)
    {
        printf("Failed to write student\n");
    }
    else
    {
        printf("Success to write\n");
    }

#endif

    fclose(fp);
    return 0;
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
    {
        printf("Catch SIGUSR1...\n");
    }
    else if(signo == SIGALRM)
    {
        printf("Catch alarm signal\n");
    }
    else
    {
        printf("Unknown signal catched\n");
    }
    return;
}

