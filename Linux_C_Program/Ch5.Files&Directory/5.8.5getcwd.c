#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char buf[100];
    char *ptr;

    memset(buf, 0x0, sizeof(buf));

    ptr = getcwd(buf, sizeof(buf));
    if (NULL == ptr)
    {
        perror("getcwd error");
        exit(-1);
    }

    printf("Current working directory: %s\n", buf);
    
    exit(0);
}