#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a=1;
    int* b = &a;
    int** c = &b;

    printf("*c is %p\n", *c);
    printf("add of b is %p\n", &b);

    printf("add of a is %p\n",&a);
    // printf("     **c is %p\n",**c);

    exit(0);
}