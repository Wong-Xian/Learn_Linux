#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
    execlp("ls", "ls", "-l", NULL);

    perror("execlp error");
    exit(-1);
}