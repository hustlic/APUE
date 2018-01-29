#include "ourhdr.h"


int main(int argc, char *argv[])
{    
    int j = 1;
    int k = 0;
    
    for(k = 1; k < 32; k++)
    {
        j = j*2;
    }
    j--;
    printf("j = %d\n", j);

    printf("max year is %d, %d\n", (j/(3600*24*365) + 1970), 3600*24*365);

    printf("max days is %d\n", (j/(3600*24*100)));

}
