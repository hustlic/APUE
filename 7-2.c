#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int a[50]={0};
//int b;
int main(int argc, char *argv[])
{
    int i = 0 ;
   
    while(environ[i] != NULL)
    {
        printf("environ[%d]=%s\n", i, environ[i]);
        i++;
    }
#if 0
    char * buf1 = alloca(100);
    for(i = 0; i < 100; i++)
    {
        buf1[i]=i;
        printf("a[%d]=%d, buf1[%d]=%d\n", i, a[i],i,buf1[i]);

    }   
    printf("%d\n", b);
#endif 
    
    
    return 0;
}
