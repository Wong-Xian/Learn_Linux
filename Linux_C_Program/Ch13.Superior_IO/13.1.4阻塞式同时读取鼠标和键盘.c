#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define MOUSE "/dev/input/event3"

int main(void)
{
    // 定义变量
    char buf[100];
    int fd, ret;

    // 打开鼠标文件描述符
    if (-1 == (fd = open(MOUSE, O_RDONLY)))
    {
        perror("open error");
        exit(-1);
    }

    // 读取鼠标设备文件内容
    memset (buf, 0, sizeof(buf));
    ret = read (fd, buf, sizeof(buf));
    printf ("鼠标：成功读取<%d>字节数据。\n", ret);

    // 读取键盘设备文件内容
    memset (buf, 0, sizeof(buf));
    ret = read (0, buf, sizeof(buf));
    printf ("键盘：成功读取<%d>字节数据。\n", ret);

    // 关闭文件、退出程序
    close(fd);
    exit(0);
}