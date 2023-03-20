#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *endptr[100]={0};

    // printf("strtol: %ld\n", strtol("0x500", NULL, 16));
    // printf("strtol: %ld\n", strtol("0x500", NULL, 0));
    // printf("strtol: %ld\n", strtol("500", NULL, 16));
    // printf("strtol: %ld\n", strtol("0777", NULL, 8));
    // printf("strtol: %ld\n", strtol("0777", NULL, 0));
    // printf("strtol: %ld\n", strtol("1111", NULL, 2));
    // printf("strtol: %ld\n", strtol("-1111", NULL, 2));

    printf("try endptr\n");
    printf("output: %ld, endptr is:%s\n", strtol(" 100",endptr,0),endptr);
    
    exit(0);
}