#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{

    char a[40] = "hello wor";
    char b[] = "ld!";

    strncat(a, b, 2);

    puts(a);

    exit(0);
}