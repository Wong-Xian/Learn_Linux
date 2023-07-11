/*
目的：通过异步IO的方式读取鼠标设备文件
关键点： O_ASYNC 标志的设置； SIGIO 信号处理函数的注册； 设置异步 IO 事件的接收进程
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define MOUSE "/dev/input/event3"

static int fd;

/* SIGIO 信号处理函数 */
static void sigio_handler(int sig)
{
    static int loops = 5;   // 定义loop静态变量，信号处理函数退出后不回收该变量
    char buf[100] = {0};    // 接收缓冲区
    int ret;

    if(SIGIO != sig)
        return;
    
    ret = read(fd, buf, sizeof(buf));   // 读取鼠标设备文件中的数据
    if (0 < ret)
        printf("鼠标: 成功读取<%d>个字节数据\n", ret);
    
    loops--;
    if (0 >= loops) // 读5次后就退出进程
    {
        close(fd);
        exit(0);
    }
}

int main(void)
{
    int flag;

    /* 打开鼠标设备文件<使能非阻塞 I/O> */
    fd = open(MOUSE, O_RDONLY | O_NONBLOCK);
    if (-1 == fd)
    {
        perror("open error");
        exit(-1);
    }

    /* 使能异步 I/O */
    flag = fcntl(fd, F_GETFL);
    flag |= O_ASYNC;
    fcntl(fd, F_SETFL, flag);

    /* 设置异步 I/O 的所有者 */
    fcntl(fd, F_SETOWN, getpid());

    /* 为 SIGIO 信号注册信号处理函数 */
    signal(SIGIO, sigio_handler);

    /* 死循环等待 */
    for ( ; ; )
        sleep(1);

    /* 此处可以继续处理其他事物，信号相当于产生外部中断。 */
}