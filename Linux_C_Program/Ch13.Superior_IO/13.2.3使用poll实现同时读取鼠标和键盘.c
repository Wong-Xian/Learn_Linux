#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<poll.h>

#define MOUSE "/dev/input/event3"

int main(void)
{
    /* 定义变量 */
    char buf[100];  // 读取键盘鼠标数据的 buf 缓冲区
    int fd, ret=0, flag;
    int loops=5;    // 循环次数 
    struct pollfd fds[2];   // 定义结构体数组，有2个数组元素

    /* 打开鼠标设备文件 */
    if (-1 == (fd = open(MOUSE, O_RDONLY | O_NONBLOCK)))
    {
        perror("open error");
        exit(-1);
    }

    /* 设置键盘为非阻塞 */
    flag = fcntl(0, F_GETFL);   // 获取原来 flag 标志
    flag |= O_NONBLOCK;         // 向 flag 中添加非阻塞标志
    fcntl(0, F_SETFL, flag);    // 设置 flag

    /* 设置键盘和鼠标的 struct pollfd 结构体 */
    fds[0].fd = 0;          // 键盘
    fds[0].events = POLLIN; // 只关心数据可读
    fds[0].revents = 0;

    fds[1].fd = fd;         // 鼠标
    fds[1].events = POLLIN; // 只关心数据可读
    fds[1].revents = 0;

    /* 循环5次读取鼠标键盘的变化 */
    while(loops--)
    {
        ret = poll(fds, 2, -1); // 传入 fds 结构体数组，共关注2个文件描述符，一直阻塞等待
        if (ret < 0)
        {
            perror("poll error");
            goto out;
        }
        
        /* 检查键盘是否为就绪态 */
        if (fds[0].revents & POLLIN)
        {
            ret = read(0, buf, sizeof(buf));    // 从标准输入设备读取数据
            if (ret > 0)
                printf("键盘: 成功读取<%d>个字节数据\n", ret);
        }

        /* 检查鼠标是否为就绪态 */
        if (fds[1].revents & POLLIN)
        {
            ret = read(fd, buf, sizeof(buf));   // 从鼠标设备读取数据
            if (ret > 0)
                printf("鼠标: 成功读取<%d>个字节数据\n", ret);
        }
    }

    out:
        /* 关闭文件 */
        close(fd);
        exit(0);
}