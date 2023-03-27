#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

int main()
{
    printf("%s\n", strsignal(SIGINT));
    printf("%s\n", strsignal(SIGALRM));
    printf("%s\n", strsignal(SIGQUIT));
    exit(0);
}