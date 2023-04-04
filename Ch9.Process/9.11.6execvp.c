#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char *arg_v[3] = {"ls", "-l", NULL};
    execvp("/bin/ls", arg_v);

    perror("execvp error");
    exit(-1);
}