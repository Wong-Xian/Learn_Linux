#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    if (-1 == mkdir("./new_dir",S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH))
    {
        perror("mkdir error");
        exit(-1);
    }

    exit(0);

}