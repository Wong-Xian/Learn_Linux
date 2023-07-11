#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int ret;
    ret = symlink("./test_file", "./soft");
    if (-1 == ret)
    {
        perror("symlink error");
        exit(-1);
    }
    exit(0);
}