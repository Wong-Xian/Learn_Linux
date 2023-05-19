#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    struct flock lock = {0};
    int fd = -1;

    /* 校验传参 */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(-1);
    }

    /* 打开文件 */
    fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        perror("open error");
        exit(-1);
    }

    /* 文件大小截断为1024字节 */
    ftruncate(fd, 1024);

    /* 对400~500字节区间加写锁 */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 400;
    lock.l_len = 100;
    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("加写锁失败");
        exit(-1);
    }

    printf("加写锁成功！\n");

    for (;;)
        sleep(1);
}