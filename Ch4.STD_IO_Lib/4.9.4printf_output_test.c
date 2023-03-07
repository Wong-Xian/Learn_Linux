#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{

    printf("Hello World!\n");
    printf("Hello World!"); // 没输出换行符
    for ( ; ; )
        sleep(1);
}

/*
标准输出默认采用的是行缓冲模式，printf()输出的字符串写入到了标准
输出的 stdio 缓冲区中，只有输出换行符时（不考虑缓冲区填满的情况）
才会将这一行数据刷入到内核缓冲区，也就是写入标准输出文件（终端设
备）
*/
