#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char *ptr = NULL;
    char str[] = "I love my home";

    ptr = strstr(str, "my");
    if (NULL != ptr)
    {
        printf("String: %s\n", ptr);
        printf("Offset: %ld\n", ptr - str);
    }
    exit(0);
}

/*
存在的缺陷：如果要找的字符不是home，而是my，此时第12行的printf输出的是从my开始到str结尾的所有字符。
*/