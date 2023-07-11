#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{

    /* 将标准输出设置为无缓冲模式*/
    if (setvbuf(stdout, NULL, _IONBF, 0))
    {
        perror("setvbuf error");
        exit(0);
    }

    printf("Hello World!\n");
    printf("Hello World!"); // 没输出换行符
    for ( ; ; )
        sleep(1);
}

