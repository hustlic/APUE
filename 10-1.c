/**
*
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sig_user(int);

static void sig_user(int signo)
{
    if(signo == SIGUSR1)
    {
        printf("catch SIGUSR1\n");
    }
    else if(signo == SIGUSR2)
    {
        printf("catch SIGUSR2\n");
    }
    else if(signo == SIGALRM)
    {
        printf("catch SIGALARM\n");
    }
    else 
    {
        printf("catch unknown signal");
    }

    return;
}

int main(int argc, char * argv[])
{
    if(signal(SIGUSR1, sig_user) == SIG_ERR)
    {
        printf("register SIGUSR1 failed\n");
    }

    if(signal(SIGUSR2, sig_user) == SIG_ERR)
    {
        printf("register SIGUSR1 failed\n");
    }

    if(signal(SIGALRM, sig_user) == SIG_ERR)
    {
        printf("register SIGUSR1 failed\n");
    }

    alarm(1);
    //pause函数是进程挂起，知道进程收到一个信号
    for(;;)
        pause();
    
}
