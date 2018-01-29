/*
*
*/
#include "ourhdr.h"
#define TEST_FILE "test.txt"

int main(void)
{
    int fd = -1;

    fd = open(TEST_FILE, O_CREAT|O_RDWR|O_TRUNC);

    if(fd < 0)
    {
        DEBUG("open failed, %s\n", strerror(errno));
        return -1;
    }

    //将标准输入，输出，出错，都重定向到fd, 也就是test.txt文件中
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    if(fd > 2)
    {
        close(fd);
    }

    printf("hello world.txt\n");
        
    return 0;
}
