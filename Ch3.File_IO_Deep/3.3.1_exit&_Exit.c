// _exit() is equal to _Exit()

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd = open("./test_file", O_RDONLY);
    if (-1 == fd)
    {
        perror("open error");
        _exit(-1);
    }
    close(fd);
    _exit(0);
}

/*
both _exit() & _Exit() are system call.
but exit() is a C function.
*/