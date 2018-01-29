/*
* File: 4-1.c
* Description: test lstat and marcos
*/
#include "ourhdr.h"

char *get_filetype(struct stat *pStat);
void set_uid(struct stat *pStat, const char* fileName);
void clear_uid(struct stat *pStat, const char* fileName);

void set_gid(struct stat *pStat, const char* fileName);
void clear_gid(struct stat *pStat, const char* fileName);

void show_uid(struct stat *pStat);
void show_gid(struct stat *pStat);
void show_dirinfo(char *path);


int main(int argc, char *argv[])
{
    struct stat mStat;

    if(argc < 2)
    {
        DEBUG("Usage: a.out <dir>");
        return -1;
    }
    
    if(lstat(argv[1], &mStat) < 0)
    {
        DEBUG("access fail %s\n", strerror(errno));
        return -1;
    }
    DEBUG("%s is %s\n", argv[1], get_filetype(&mStat));

    //符号链接的长度是它指向的第一个文件的文件名长度
    //link2--->link111111-->1.txt
    //link2的长度是10，link111111的长度是5
    if(S_ISREG(mStat.st_mode) || S_ISLNK(mStat.st_mode) || S_ISDIR(mStat.st_mode))
    {
        DEBUG("%s, size=%d\n", argv[1], mStat.st_size);
    }
    
    //对link文件的操作，会直接作用于link指向的实际的文件
    if(S_ISREG(mStat.st_mode) || S_ISLNK(mStat.st_mode))
    {
        DEBUG("%s, st_mode=%d\n", argv[1], mStat.st_mode);
        if(S_ISUID & mStat.st_mode)
            DEBUG("%s, uid is set\n", argv[1]);
        if(S_ISGID & mStat.st_mode)
            DEBUG("%s, gid is set\n", argv[1]);

        set_uid(&mStat,argv[1]);
        set_gid(&mStat,argv[1]);
        show_uid(&mStat);
        show_gid(&mStat);

        #if 0
        clear_uid(&mStat,argv[1]);
        clear_gid(&mStat,argv[1]);
        show_uid(&mStat);
        show_gid(&mStat);
        #endif
    }

    //show_dirinfo(argv[2]);
    return 0;
}

char *get_filetype(struct stat *pStat)
{
    if(S_ISREG(pStat->st_mode))
       return "regular file";
    else if(S_ISDIR(pStat->st_mode))
       return "directory";
    else if(S_ISCHR(pStat->st_mode))
       return "char device file";
    else if(S_ISBLK(pStat->st_mode))
       return "block device file";
    else if(S_ISFIFO(pStat->st_mode))
       return "fifo file";
    else if(S_ISLNK(pStat->st_mode))
       return "link file";
    else if(S_ISSOCK(pStat->st_mode))
       return "socket file";
    else
       return "unknown file type";
}

void show_dirinfo(char *path)
{
    DIR *dp;
    struct dirent *dirp;
    struct stat mStat;
    char file_name[1024]={0};
    
    if( NULL == (dp = opendir(path)) )
    {
        DEBUG("can not open %s, %s\n", path, strerror(errno));
        return;
    }
    
    //iterator the directory
    while( NULL != (dirp = readdir(dp) ) )
    {
        memset(file_name,0,1024);
        strcat(file_name,path);
        strcat(file_name,"/");
        strcat(file_name,dirp->d_name);
        if(lstat(file_name, &mStat) < 0)
        {
            DEBUG("%s, lstat error, %s\n", dirp->d_name, strerror(errno));
            continue;
        }
        if(S_ISREG(mStat.st_mode))
        {
            DEBUG("%s, %s\n", file_name, get_filetype(&mStat));
            show_uid(&mStat);
            show_gid(&mStat);
        }
    }

    closedir(dp);
}

void set_uid(struct stat *pStat, const char *fileName)
{
    pStat->st_mode |= S_ISUID;
    chmod(fileName, pStat->st_mode);
}
void clear_uid(struct stat *pStat, const char *fileName)
{
    pStat->st_mode &= ~S_ISUID;
    chmod(fileName, pStat->st_mode);
}

void set_gid(struct stat *pStat, const char *fileName)
{
    pStat->st_mode |= S_ISGID;
    chmod(fileName, pStat->st_mode);
}
void clear_gid(struct stat *pStat, const char *fileName)
{
    pStat->st_mode &= ~S_ISGID;
    chmod(fileName, pStat->st_mode);
}

void show_uid(struct stat *pStat)
{
    DEBUG("uid is %s,\n", (pStat->st_mode & S_ISUID)?("set"):("clear"));
}
void show_gid(struct stat *pStat)
{
    DEBUG("gid is %s,\n", (pStat->st_mode & S_ISGID)?("set"):("clear"));
}

