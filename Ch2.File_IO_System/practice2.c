#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int ret = open ("./test.txt",
                    O_CREAT|O_EXCL|O_RDONLY,
                    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (ret==-1)
    {
        printf ("file \"test.txt\" has already exist.\n");
        return ret;
    }
    else
    {
        printf("file do not exist, creating it...\n");
        close(ret);
        return 0;
    }
}