#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *arg_v[4]={"ls", "-a", "-l", NULL};

    execv("/bin/ls", arg_v);

    perror("execv error");
    exit(-1);
}