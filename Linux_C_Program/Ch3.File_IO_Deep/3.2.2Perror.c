#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

// describtion: print a system error message
// void  perror(const char *s);  's' is additional information

int main(void)
{
    int fd = open("./test_file", O_RDONLY);
    if (-1 == fd)
    {
        perror("open error");   // ": " will be added automatically.
        return -1;
    }
    close(fd);
    return 0;
}