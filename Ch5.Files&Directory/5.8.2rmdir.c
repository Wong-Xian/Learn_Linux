#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int ret;
    ret = rmdir("./new_dir");
    if (-1 == ret)
    {
        perror("rmdir error");
        exit(-1);
    }
    exit(0);
}