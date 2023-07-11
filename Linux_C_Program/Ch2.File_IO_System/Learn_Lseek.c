/*
Learn system call function lseek

need to include headers:

    #include <sys/types.h>

    #include <unistd.h>

origional func:

    off_t lseek(int fd, off_t offset, int whence);

*/

#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

void main()
{
    int fd = open("./app.c",O_RDONLY);  // open a file.

    off_t off = lseek(fd, 0, SEEK_SET);
    if (-1 == off)
        return -1;
    // this will set the ReadWriteFlag to the start of the file, which is 0.

    off_t off = lseek(fd, 0, SEEK_END);
    if (-1 == off)
        return -1;
    // this will set the ReadWriteFlag to the end of the file.

    off_t off = lseek(fd, 100, SEEK_SET);
    if (-1 == off)
        return -1;
    // this will set the Flag shift 100 from the start of the file, which is 100.

    off_t off = lseek(fd, 0, SEEK_CUR);
    if (-1 == off)
        return -1;
    // Fetch the Flag.
}