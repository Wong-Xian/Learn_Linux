#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    size_t len;
    len = strlen("hello world!\n\0");

    printf("lenth of string is %ld Bytes.\n",len);

    exit(0);
}