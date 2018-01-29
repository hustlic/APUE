/*
* File: 1-1.c
* Pratice: 
*        opendir -- open specified directory
*        readdir -- read opened dir, return dirp
*
*/
#include "ourhdr.h"

int main( int argc, char *argv[] )
{
    DIR *dp;
    struct dirent *dirp;

    if( argc != 2 )
    {
        err_quit("a single argument (the dir name ) is required\n");
        
    }

    if( NULL == (dp = opendir(argv[1])) )
    {
        err_sys("can not open %s\n", argv[1]);        
    }

    //iterator the directory
    while( NULL != (dirp = readdir(dp) ) )
    {
        err_info("%s\n", dirp->d_name);        
    }

    closedir(dp);
    exit(0);

}