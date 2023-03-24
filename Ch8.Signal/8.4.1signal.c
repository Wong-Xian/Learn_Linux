#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 自定义信号处理函数
static void sig_handler(int sig)
{
    printf("Received signal: %d\n", sig);
}

int main(int argc, char *argv[])
{
    sig_t ret = NULL;
    // 将SIGINT信号与自定义处理函数绑定
    ret = signal(SIGINT, (sig_t)sig_handler);

    if (SIG_ERR == ret) // 判断绑定是否成功
    {
        perror("signal error");
        exit(-1);
    }

    /* 死循环，等待中断 */
    for ( ; ; ) { }

    exit(0);
}