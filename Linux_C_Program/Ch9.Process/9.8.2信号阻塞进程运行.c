#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

static void sig_handler(int sig)
{
    printf("接收到信号\n");
}

int main(void)
{
    struct sigaction sig = {0};
    sigset_t wait_mask;

    /* 初始化信号集 */
    sigemptyset(&wait_mask);

    /* 设置信号处理方式 */
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;

    if (-1 == sigaction(SIGUSR1, &sig, NULL))
    {
        perror("sigaction error");
        exit(-1);
    }

    switch (fork())
    {
        case -1:
            perror("fork error");
            exit(-1);
        case 0:
            /* 子进程 */
            printf("子进程开始执行\n");
            printf("子进程打印信息\n");
            printf("~~~~~~~~~~~~~~~\n");
            sleep(2);
            kill(getppid(), SIGUSR1); //发送信号给父进程、唤醒它
            _exit(0);
        default:
            /* 父进程 */
            // pause();
            
            if (-1 != sigsuspend(&wait_mask))//不阻塞任何信号，并挂起。
                exit(-1);
            
            
            printf("父进程开始执行\n");
            printf("父进程打印信息\n");
            exit(0);
    }
}

/*
Sum:
    wait_mask信号集的设置不是必须的。该程序中设置的这个信号集是个空信号集，
    意味着在父进程中不阻塞任何信号，而直接挂起。sigsuspend函数是将
    sigprocmask函数和pause函数封装成原子函数，在不必要设置sigprocmask的
    时候，可以直接调用pause函数，而不会对程序的功能产生任何影响。
*/