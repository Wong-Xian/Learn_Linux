#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ret;
    ret = chmod("./test_file", 0777);
    if (-1 == ret)
    {
        perror("chmod error");
        exit(-1);
    }
    exit(0);
}