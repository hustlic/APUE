#include "ourhdr.h"

int main(int argc, char *argv[])
{
    //strerror need string.h
    fprintf(stderr, "EAcess: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror("LICHENG");
    return 0;
}