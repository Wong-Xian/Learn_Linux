#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    printf("Hello World!\n");
    printf("Hello World!");
    // return 0;    // 退出时可自动刷新缓冲区
    // exit(0);     // 退出时可自动刷新缓冲区
    // _exit(0);    // 退出时【不能】自动刷新缓冲区
}