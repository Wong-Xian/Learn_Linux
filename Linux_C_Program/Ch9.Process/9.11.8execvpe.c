#define _GNU_SOURCE // 一定要添加这一行，否则报警告，隐式声明有误。
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main()
{
    char *arg_v[4]={"ls", "-l", NULL};
    execvpe("ls",arg_v, environ);

    perror("execvpe error");
    exit(-1);
}