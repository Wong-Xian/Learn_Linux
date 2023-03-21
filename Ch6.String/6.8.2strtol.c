#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    #if 1   // strtol第二个参数不为NULL的情况
        int ret;
        char a[3] = {'a','b','c'};
        char *b = a;

        ret = strtol("hello world!", &b, 0);
        printf("ret:%d\n", ret);

        printf("%s\n", b);
    #endif

    #if 0   // strtol第二个参数为NULL的情况
        printf("strtol: %ld\n", strtol("0x500", NULL, 16));
        printf("strtol: %ld\n", strtol("0x500", NULL, 0));
        printf("strtol: %ld\n", strtol("500", NULL, 16));
        printf("strtol: %ld\n", strtol("0777", NULL, 8));
        printf("strtol: %ld\n", strtol("0777", NULL, 0));
        printf("strtol: %ld\n", strtol("1111", NULL, 2));
        printf("strtol: %ld\n", strtol("-1111", NULL, 2));
    #endif

    exit(0);
}