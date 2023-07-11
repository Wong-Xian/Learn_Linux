#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>

void test()
{
    // test open file error
    int fd = open("./test.txt",O_RDONLY);
    if (fd==-1)
    {
        printf("Error:%s\nerrno is %d\n",strerror(errno),errno);
    }
}

void test2()
{
    for (int i=0; i<50; i++)
    {
        printf("errno:%d, Error:%s\n", i, strerror(i));
    }
}

int main()
{
    test();
    test2();
    return 0;
}