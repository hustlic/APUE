/**
* 使用popen,将读入的文件，输出到分页器中
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 1024
#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[])
{
    FILE *fpin, *fpout;
    char buf[512]={0};
    
    if((fpin = fopen(argv[1],"r")) == NULL)
    {
        printf("Failed to open %s\n", argv[1]);
        return -1;
    }

    if((fpout=popen(PAGER, "w"))==NULL)
    {
        printf("Faild to popen\n");
        return -1;
    }

    while(fgets(buf,MAX_LINE,fpin) != NULL)
    {
        fputs(buf,fpout);
        memset(buf,0,sizeof(buf));
    }

    

    return 0;
}

