#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int age;
    int gender;
    char name[20];
}student;

int main(void)
{
    student stu1;    

    student stu1_bk;

    FILE *fp = fopen("fopen.txt", "a+");

    //printf("fd=%d\n", fileno(fp));
    
    stu1.age = 18;
    stu1.gender = 1;

    //memcpy(stu1.name, "Lileilei", strlen("Lileilei"));此处会导致fread的时候的内容不一致
    memcpy(stu1.name, "Lileilei", sizeof(stu1.name));

    //fputs("ctrl_interface=123\nhelloworld\n", fp);

    if(fwrite(&stu1, sizeof(stu1), 1, fp) != 1)
    {
        printf("Failed to write student\n");
    }

    fclose(fp);

    fp = fopen("fopen.txt", "rb");
    
    fread(&stu1_bk, sizeof(student), 1, fp);

    printf("stu1_bk.age=%d\n", stu1_bk.age);
    printf("stu1_bk.gender=%d\n", stu1_bk.gender);
    printf("stu1_bk.name=%s\n", stu1_bk.name);

    fclose(fp);
    return 0;
}
