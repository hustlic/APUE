#include <sys/time.h>
#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{

    struct rlimit mylimit;

    #ifdef RLIMIT_DATA
    if(getrlimit(RLIMIT_DATA, &mylimit) < 0)
        printf("Error, %s\n",strerror(errno));
    #else
    #error RLIMIT_DATA not supported
    #endif

    if(mylimit.rlim_cur == RLIM_INFINITY)
    {
        printf("infinity\n");
    }
    else
    {
        printf("%10ld\n", mylimit.rlim_cur);
    }

    int i = 0;
    while(i < 1000)
    {
        printf("uid=%d, euid=%d\n", getuid(), geteuid());
        sleep(1);
    }
    return 0;

}
