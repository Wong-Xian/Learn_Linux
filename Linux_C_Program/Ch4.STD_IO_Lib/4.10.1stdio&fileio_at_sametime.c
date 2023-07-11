/*
注意同时使用stdio（标准库）和文件IO（系统调用）时
二者对缓冲区的控制的区别。
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("print");
    write(STDOUT_FILENO, "write\n", 6);
    exit(0);
}

/*
printf是标准函数（C库），默认行缓冲，此时没有"\n"换行符，因此
数据在stdio缓冲区，没刷入到内核缓冲区。
write函数是系统调用，直接写入到内核缓冲区，因此先显示到屏幕上
*/