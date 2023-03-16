#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int ret;
    ret = rename("./test_file", "./new_file");
    if (-1 == ret)
    {
        perror("rename error");
        exit(-1);
    }
    exit(0);
}