#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main()
{
    execle("/bin/ls", "ls", "-l", NULL, environ);

    perror("execle error");
    exit(-1);
}