#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("uid: %d\n", getuid());
    if (-1 == chown("./test_file", 0, 0))
    {
        perror("chown error");
        exit(-1);
    }
    exit(0);
}