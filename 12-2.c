/**
* 作为daemon进程启动， 创建pid文件，并持有1把写锁
*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


#define PID_FILE "mypid"

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

#define write_lock(fd, offset, whence,len)\
        lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)


int main()
{
    char buf[32] = {0};

    int val = 0;
    
    int fd = open(PID_FILE, O_WRONLY |O_CREAT);
    if(fd < 0)
    {
        printf("open file %s failed", PID_FILE);
        return -1;
    }

    //添加写锁
    if(write_lock(fd, 0, SEEK_SET, 0) < 0)
    {
        printf("failed to create write lock\n");
        return -1;
    }

    //文件长度清零
    if(ftruncate(fd,0)< 0)
    {
        printf("failed to ftruncate to 0\n");
        return -1;
    }

    sprintf(buf, "%d\n", getpid());
    if(write(fd, buf, strlen(buf)) != strlen(buf))
    {
        printf("failed to write pid to file\n");
        return -1;
    }

    //set close on exec flag
    if( val = fcntl(fd, F_GETFD, 0) < 0)
    {
        printf("failed to get fd flag\n");
        return -1;
    }
    val |= FD_CLOEXEC;
    if(fcntl(fd, F_SETFD, val))
    {
        printf("failed to set close on exec\n");
        return -1;
    }

    pause();
    exit(0);
    
}
