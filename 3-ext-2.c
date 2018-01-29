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

    //����׼���룬������������ض���fd, Ҳ����test.txt�ļ���
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
