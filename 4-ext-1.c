/**
* File 4-ext-1
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
    struct stat my_stat;
    int ret = -1;

    if(argc <= 1)
    {
        printf("Usage: ./a.out <file>\n");
        return -1;
    }
    
    ret = lstat(argv[1], &my_stat);

    if(S_ISREG(my_stat.st_mode))
    {
        printf("Regular file\n");
    }
    else
    {
        printf("Not reg file\n");
    }

    if(S_ISLNK(my_stat.st_mode))
    {
        printf("Link file\n");
        char namebuf[128]={0};
        int len=readlink(argv[1], namebuf, 128);
        namebuf[len]=0;
        printf("%s---->%s\n", argv[1], namebuf);
        
    }

    {
        int ret = rmdir("testdir");
        printf("ret=%d\n", ret);

        if(ret!=0)
            printf("%s\n", strerror(errno));
    }
    //others
    //S_ISLNK,S_ISDIR,
    return 0;

}
