#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    if (-1 == link("./test_file", "./hard"))
    {
        perror("link error");
        exit(-1);
    }
    exit(0);
}