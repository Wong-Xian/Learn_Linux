/*
程序目的：
    给进程自身使用alarm函数设定计时器，当定时器归零时，打印提升。
*/

#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

static void sig_handler()
{
    printf("times' up!\n");
    exit(0);
}

int main()
{
    struct sigaction sa = {0};
    int ret;

    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;

    ret = sigaction(SIGALRM, &sa, NULL);// 绑定信号处理方式
    if (-1 == ret)
    {
        perror("sigaction error");
        exit(-1);
    }

    alarm(5);   // 设定5s倒计时

    while(1)
    {
        printf("hello world!\n");
        sleep(1);
    }
}