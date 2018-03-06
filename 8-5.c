#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("Before fork\n");

    pid = fork();

    if(pid > 0)
    {

    }
    else if(pid == 0)
    {
        printf("First child, fork again\n");
        pid_t pid2 = fork();

        if(pid2 > 0)
        {
            printf("First child exit\n");
            sleep(5);
            exit(0);
        }
        else if(pid2 == 0)
        {
            sleep(15);
            printf("Second child, father is %d\n", getppid());
        }
        else
        {
            printf("2nd Fork error\n");
        }
    }
    else
    {
        printf("1st fork error\n");
    }

    waitpid(pid, NULL, 0);

    return 0;

}
