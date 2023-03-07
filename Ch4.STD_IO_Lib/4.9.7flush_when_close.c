#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    printf("Hello World!\n");
    printf("Hello World!");
    fclose(stdout); //关闭标准输出
    for ( ; ; )
        sleep(1);
}

/*
sum:
    关闭文件时会自动刷新文件的stdio缓冲区
*/