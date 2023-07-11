#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *base = NULL;
    int ret;

    /* 申请内存: 256 字节对齐*/
    ret = posix_memalign((void **)&base, 256, 1024);//此处对base取地址，相当于形成了一个二级指针，该指针指向base变量。
    if (0 != ret)
    {
        printf("posix_memalign error\n");
        exit(-1);
    }

    /* 使用内存 */
    // base[0] = 0;
    // base[1] = 1;
    // base[2] = 2;
    // base[3] = 3;

    /* 释放内存 */
    free(base);

    exit(0);
}