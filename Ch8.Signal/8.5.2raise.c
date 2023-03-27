#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_handler(int sig)    // 定义信号处理函数
{
    printf("Received signal: %d\n", sig);// 打印出信号对应的序号
}

int main()
{
    struct sigaction sig = {0}; // 定义结构体变量，并初始化为0
    int ret;

    sig.sa_handler = sig_handler;// 指定信号处理函数
    sig.sa_flags = 0;

    ret = sigaction(SIGQUIT, &sig, NULL);// 绑定信号处理方式
    if (-1 == ret)
    {
        perror("sigaction error");
        exit(-1);
    }

    for ( ; ; )
    {
        /* 向自身发送 SIGINT 信号 */
        if (0 != raise(SIGQUIT))
        {
            printf("raise error\n");
            exit(-1);
        }
        sleep(3); // 每隔 3 秒发送一次
    }

    exit(0);
}