#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *user_name = NULL;
    
    if(argc != 2)
    {
        printf("Usage: ./a.out [name]\n");
        return -1;
    }
    
    user_name = argv[1];
    
    struct passwd * user = getpwnam(user_name);

    if(user != NULL)
    {
        printf("passwd is %s, name is %s\n",user->pw_passwd, user->pw_name);
        printf("uid = %d, gid = %d\n", user->pw_uid, user->pw_gid);
        printf("realname is %s\n", user->pw_gecos);
        printf("home dir is %s\n", user->pw_dir);
        printf("Shell is %s\n", user->pw_shell);
    }
    return 0;
}
