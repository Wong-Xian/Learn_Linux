#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char s1[100]="hello world,";
    char s2[]="welcome to the world!";

    strcat(s1, s2);
    puts(s1);
    
    exit(0);
}