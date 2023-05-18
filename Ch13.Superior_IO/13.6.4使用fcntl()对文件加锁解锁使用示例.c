#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[])
{
    /* 定义变量 */
    struct flock lock = {0};
    int fd = -1;
    char buf[] = "Hello world!";

    /* 校验传参 */
    if (argc != 2)
    {
        fprintf (stderr, "usage: %s <file>\n", argv[0]);
        exit(-1);
    }

    /* 打开文件 */
    fd = open (argv[1], O_WRONLY);
    if (fd == -1)
    {
        perror ("open error");
        exit(-1);
    }

    /* 对文件加锁 */
    lock.l_type = F_WRLCK;      // 锁类型为独占性写锁
    lock.l_whence = SEEK_SET;   // 起始处：文件头
    lock.l_start = 0;           // 偏移量为0
    lock.l_len = 0;             // 锁范围：全文
    if (fcntl (fd, F_SETLK, &lock))
    {
        perror("加锁失败");
        exit(-1);
    }

    printf("对文件加锁成功");

    /* 对文件进行写操作 */
    if (0 > write(fd, buf, strlen(buf)))
    {
        perror ("write error");
        exit(-1);
    }

    /* 解锁 */
    lock.l_type = F_UNLCK;  // 解锁
    fcntl(fd, F_SETLK, &lock);

    /* 退出 */
    close(fd);
    exit(0);
}