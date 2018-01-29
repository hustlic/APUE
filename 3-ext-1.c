#include "ourhdr.h"


#define TEST_FILE "test.txt"
#define OPEN_MAX 1024

/** 实现一个和dup2相同的函数，要求不能使用fcntl函数
* 用fd_out指定新的文件描述符，若fd_out已经打开，则关闭
* 若fd_out等于fd_in, 则直接返回fd_out
*/
int dup2_fake(int fd_in, int fd_out)
{
    int ret = 0;
    int fd = -1;
    int temp_fd = -1;
    int fd_array[OPEN_MAX] = {0};
    int cnt = 0;
    
    char buf[20]={0};
    
    if(fd_in > OPEN_MAX || fd_out > OPEN_MAX)
    {
        DEBUG("invalid param fd_in=%d, fd_out=%d, OPEN_MAX=%d\n", fd_in, fd_out,OPEN_MAX);
        return -1;
    }
                
    sprintf(buf, "/proc/%d/fd/%d", getpid(),fd_in);

    if(access(buf,0) != 0)
    {        
        DEBUG("the old fd(%d) is not opened, ret=%d, %s\n", fd_in, ret,strerror(errno));
        return -1;
    }

    if(fd_out == fd_in)
    {
        DEBUG("fd_out is same as fd_in\n");
        return fd_out;
    }

    memset(buf,0,sizeof(buf));
    sprintf(buf,"/proc/%d/fd/%d", getpid(), fd_out);
    if(access(buf, 0) == 0)
    {
        DEBUG("new fd(%d) is already opened, close it first\n", fd_out);
        close(fd_out);
    }
    DEBUG("new fd is not used, dup2 to it\n");    
    
    temp_fd = -1;
       
    while((temp_fd = dup(fd_in)) && (cnt < OPEN_MAX))
    {
        if(temp_fd == fd_out)
        {
            DEBUG("found fd\n");
            break;
        }
        else
        {
            DEBUG("add new fd(%d) to array[%d]\n", temp_fd, cnt);
            fd_array[cnt++]=temp_fd;
        }        
    }
    
    while(cnt>0)
    {     
        DEBUG("closing %d\n", fd_array[cnt]);
        close(fd_array[cnt--]);        
    }

    DEBUG("return %d\n", temp_fd);
    return temp_fd;

}

int main(void)
{
    int fd = -1;

    int fd_out = -1;

    fd = open(TEST_FILE, O_RDWR);

    if(fd < 0)
    {
        DEBUG("failed to open %s\n",TEST_FILE);
    }
    
    fd_out = dup2_fake(fd, 100);
        
    DEBUG("new fd is %d\n", fd_out);
    
}
