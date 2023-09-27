/* 就版本的Linux 只能使用creat函数创建文件，再close它，再open它，接着才能对其
进行操作 */

#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int fd = creat("creat.txt", S_IWUSR);
    printf ("fd = %d\n", fd);
    return fd;
}

/* 首次执行程序成功，返回fd=3；若文件已经存在，执行该程序，返回-1 */