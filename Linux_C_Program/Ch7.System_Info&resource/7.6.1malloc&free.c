#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC_MEM_SIZE (1024)

int main()
{
    char *base = NULL;

    /* 申请堆内存 */
    base = (char*)malloc(MALLOC_MEM_SIZE);
    if (NULL == base)
    {
        printf("malloc error\n");
        exit(-1);
    }

    /*读取内存空间内的数据*/
    printf("内存中数据：\n%s\n", base);

    /* 初始化申请到的堆内存 */
    memset(base, 0x0, MALLOC_MEM_SIZE);

    /*再次读取内存中数据*/
    printf("内存中数据：\n%s\n", base);

    /* 释放内存 */
    free(base);

    exit(0);
}

/*
sum：
    未初始化之前，分配的内存中内容不可预测，使用前要初始化。
*/