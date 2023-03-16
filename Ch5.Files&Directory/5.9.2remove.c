#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ret;

    ret = remove("./test_file");
    if (-1 == ret)
    {
        perror("remove error");
        exit(-1);
    }
    
    exit(0);
}