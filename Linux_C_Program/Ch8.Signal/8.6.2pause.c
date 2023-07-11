/*
目的：
    验证pause函数。设定定时器，将程序pause，等待定时器的到来。
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

static void sig_handler()
{
    printf("times' up!\n");
}

int main(int argc, char *argv[])
{
    // 定义信号处理结构体
    struct sigaction sa = {0};
    int seconds;
    int ret;

    if (argc > 2)
    {
        exit(-1);
    }

    // 配置信号处理结构体
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;

    // 绑定信号处理的结构体
    sigaction(SIGALRM, &sa, NULL);

    // 将输入的秒数转换成int类型数据
    seconds = atoi(argv[1]);
    printf("alarm set at %d seconds.\n", seconds);

    // 设置定时器
    alarm(seconds);

    // 休眠，等待唤醒
    ret = pause();
    if (-1 == ret)
    {
        perror("pause interrupted");
    }

    exit(0);
}