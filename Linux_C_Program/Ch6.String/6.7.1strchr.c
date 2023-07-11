#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *ptr = NULL;
    char str[] = "Hello World!";

    ptr = strchr(str, 'W');
    if (NULL != ptr)
    {
        printf("Character: %c\n", *ptr);
        printf("Offset: %ld\n", ptr - str);
    }
    else
    {
        printf("No such character!\n");
    }

    exit(0);
}

/*
sum:
    如用puts输出ptr，则会把W字符后面的剩余字符也一同输出。
*/