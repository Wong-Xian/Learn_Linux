#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("atoi1:\t%d\n", atoi("that is 500"));
    printf("atoi2:\t%d\n", atoi("500"));
    printf("atol:\t%ld\n", atol("500"));
    printf("atoll:\t%lld\n", atoll("500"));
    exit(0);
}

/*
sum:
    将【字符串数据类型】的数字转换成【整型数据类型】的数字。
    被转换的字符串中不能含有除了数字以外的其他字符，否则转换失败。
*/