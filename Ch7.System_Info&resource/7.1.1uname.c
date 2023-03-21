#include<sys/utsname.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    struct utsname A;
    int ret;

    ret = uname(&A);
    if (ret == -1)
    {
        perror("uname error");
        exit(-1);
    }


    printf("sysname: %s\n",A.sysname);
    printf("nodename: %s\n",A.nodename);
    printf("release: %s\n",A.release);
    printf("vesion: %s\n",A.version);
    printf("machine: %s\n",A.machine);

    exit(0);
}