#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, int *argv[])
{
    /* 定义变量 */
    struct flock wr_lock = {0};     // 定义 flock 结构体变量 写锁
    struct flock rd_lock = {0};     // 定义 flock 结构体变量 读锁
    int fd = -1;                    // 定义文件描述符

    /* 校验传参 */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(-1);
    }

    /* 打开文件 */
    fd = open (argv[1], O_RDWR);
    if (fd == -1)
    {
        perror ("open error");
        exit(-1);
    }

    /* 将文件大小截断为1024字节 */
    ftruncate (fd, 1024);

    /* 对100~200字节区间加写锁 */
    wr_lock.l_type = F_WRLCK;       // 
    wr_lock.l_whence = SEEK_SET;
    wr_lock.l_start = 100;
    wr_lock.l_len = 100;
    if (fcntl(fd, F_SETLK, &wr_lock))
    {
        perror("加写锁失败");
        exit(-1);
    }

    printf("加写锁成功！\n");

    /* 对400~500字节区间加读锁 */
    rd_lock.l_type = F_RDLCK;
    rd_lock.l_whence = SEEK_SET;
    rd_lock.l_start = 400;
    rd_lock.l_len = 100;
    if (fcntl(fd, F_SETLK, &rd_lock))
    {
        perror("加读锁失败");
        exit(-1);
    }

    printf("加读锁成功！\n");

    /* 接下来可以对文件进行IO操作 */

    /* 解锁 */
    wr_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &wr_lock);

    rd_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &rd_lock);

    /* 退出 */
    close(fd);
    exit(0);
}
