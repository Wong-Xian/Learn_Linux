#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    // setvbuf(stdout, NULL, _IONBF, 0);
    // 通过setvbuf关闭stdio流的缓冲功能。
    printf("Hello World!");
    
    switch (fork())
    {
        case -1:
            perror("fork error");
            exit(-1);
        case 0:
            /* 子进程 */
            exit(0);
        default:
            /* 父进程 */
            exit(0);
    }
}