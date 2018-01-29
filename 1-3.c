#include "ourhdr.h"

int main(void)
{
    int c;

    while ( (c=getc(stdin)) != EOF )
    {
        if( (putc(c, stdout)) == EOF )
        {
            err_quit("put err");
        }

        if(ferror(stdin))
        {
            err_sys("input error");
        }
        exit(0);
    }


}