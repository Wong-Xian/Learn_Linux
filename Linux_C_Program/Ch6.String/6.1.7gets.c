#include<stdio.h>
#include<stdlib.h>

int main()
{
    char si[10]={0};
    char* s=&si;

    if (NULL==gets(s))
    {
        perror("gets error");
        exit(-1);
    }

    puts(s);    // 输出

    exit(0);
}