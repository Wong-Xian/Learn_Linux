/*
测试【标准输入函数】的参数使用。
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    // define var
    int d1,d2;
    char s1[20]={"hello world!"};
    char* buf;

    // 测试%*d跳过某个输入
    // printf("输入3个数，第二个数将不会被保存。\n");
    // scanf("%d %*d %d", &d1, &d2);
    // printf("输入的第一个数是：%d，输入的第三个数是：%d。\n", d1, d2);

    // 测试%ms  自动分配缓冲区，不需要手动分配
    scanf("%ms", &buf);
    printf("%s\n", buf);
    // 注意，不能有空格，因为空格会被认为是字符串的结束。
    free(buf);  // 用完要free掉内存空间

    return 0;
}