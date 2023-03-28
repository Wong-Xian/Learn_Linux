# Ch8 信号（基础）

为什么要学信号：在很多应用程序当中，都会存在处理异步事件这种需求，而信号提供了一种处理异步事件的方法。

## 8.1 基本概念

信号是事件发生时对进程的通知机制，也可以把它称为软件中断。一个具有合适权限的进程能够向另一个进程发送信号。信号的目的是用于通信。

信号由谁处理，怎么处理：信号通常是发送给对应的进程，当信号到达后，该进程需要做出相应的处理措施。

信号是异步的：产生信号的事件对进程而言是随机出现的，进程无法预测该事件产生的准确时间，进程不能够通过简单地测试一个变量或使用系统调用来判断是否产生了一个信号。

信号本质上是 int 类型数字编号：内核针对每个信号，都给其定义了一个唯一的整数编号，从数字 1 开始顺序展开。并且每一个信号都有其对应的名字（其实就是一个宏），信号名字与信号编号乃是一一对应关系，但是由于每个信号的实际编号随着系统的不同可能会不一样，所以在程序当中一般都使用信号的符号名（也就是宏定义）。

## 8.2 信号的分类

可靠性分类：
- 可靠信号
- 不可靠信号

实时性分类：
- 实时信号
- 非实时信号

### 8.2.1 可靠信号 与 不可靠信号

不可靠信号可能丢失。可靠信号支持排队，不会丢失。

### 8.2.2 实时信号 与 非实时信号

非实时信号都不支持排队，都是不可靠信号。

实时信号都支持排队，都是可靠信号。

## 8.3 常见信号 与 默认行为

Linux 下对标准信号（不可靠信号、非实时信号）的编号为 1~31，对这些信号的系统默认操作如下：

- SIGINT

当用户在终端按下中断字符（通常是 CTRL + C）时，内核将发送 SIGINT 信号给前台进程组中的每一个进程。该信号的系统默认操作是<b>终止进程的运行</b>。所以通常我们都会使用 CTRL + C 来终止一个占用前台的进程，原因在于大部分的进程会将该信号交给系统去处理，从而执行该信号的系统默认操作。

- SIGQUIT

当用户在终端按下退出字符（通常是 CTRL + \）时，内核将发送 SIGQUIT 信号给前台进程组中的每一个进程。该信号的系统默认操作是<b>终止进程的运行、并生成可用于调试的核心转储文件</b>。进程如果陷入无限循环、或不再响应时，使用 SIGQUIT 信号就很合适。所以对于一个前台进程，既可以在终端按下中断字符CTRL + C、也可以按下退出字符 CTRL + \来终止，当然前提条件是，此进程会将 SIGINT 信号或 SIGQUIT信号交给系统处理（也就是没有将信号忽略或捕获），进入执行该信号所对应的系统默认操作。

- SIGILL

如果进程试图执行非法（即格式不正确）的机器语言指令，系统将向进程发送该信号。该信号的系统默认操作是<b>终止进程的运行</b>。

- SIGABRT

当进程调用 abort()系统调用时（进程异常终止），系统会向该进程发送 SIGABRT 信号。该信号的系统默认操作是<b>终止进程、并生成核心转储文件</b>。

- SIGBUS

产生该信号（总线错误，bus error）表示发生了某种内存访问错误。该信号的系统默认操作是<b>终止进程</b>。

- SIGFPE

该信号因特定类型的算术错误而产生，譬如除以 0。该信号的系统默认操作是<b>终止进程</b>。

- SIGKILL

此信号为“必杀（sure kill）”信号，用于杀死进程的<b>终极办法</b>，此信号无法被进程阻塞、忽略或者捕获，故而“一击必杀”，总能终止进程。使用 SIGINT 信号和 SIGQUIT 信号虽然能终止进程，但是前提条件是<u>该进程并没有忽略或捕获这些信号</u>，如果使用 SIGINT 或 SIGQUIT 无法终止进程，那就使用“必杀信号”SIGKILL 吧。Linux 下有一个 kill 命令，kill 命令可用于向进程发送信号，我们会使用"kill -9 xxx"命令来终止一个进程（xxx 表示进程的 pid），这里的-9 其实指的就是发送编号为 9 的信号，也就是 SIGKILL 信号。

- SIGUSR1

该信号和 SIGUSR2 信号供程序员自定义使用，内核绝不会为进程产生这些信号，在我们的程序中，可以使用这些信号来互通通知事件的发生，或是进程彼此同步操作。该信号的系统默认操作是<b>终止进程</b>。

- SIGSEGV

这一信号非常常见，当应用程序对内存的引用无效时，操作系统就会向该应用程序发送该信号。引起对内存无效引用的原因很多，C 语言中引发这些事件往往是解引用的指针里包含了错误地址（譬如，未初始化的指针），或者传递了一个无效参数供函数调用等。该信号的系统默认操作是<b>终止进程</b>。

- SIGUSR2

与 SIGUSR1 信号相同。

- SIGPIPE

涉及到管道和 socket，当进程向已经关闭的管道、FIFO 或套接字写入信息时，那么系统将发送该信号给进程。该信号的系统默认操作是<b>终止进程</b>。

- SIGALRM

与系统调用 alarm()或 setitimer()有关，应用程序中可以调用 alarm()或 setitimer()函数来设置一个定时器，当定时器定时时间到，那么内核将会发送 SIGALRM 信号给该应用程序，关于 alarm()或 setitimer()函数的使用，后面将会进行讲解。该信号的系统默认操作是<b>终止进程</b>。

- SIGTERM

这是用于终止进程的标准信号，也是 kill 命令所发送的默认信号（kill xxx，xxx 表示进程 pid），有时我们会直接使用"kill -9 xxx"显式向进程发送 SIGKILL 信号来终止进程，然而这一做法通常是错误的，<u>精心设计的应用程序应该会捕获 SIGTERM 信号、并为其绑定一个处理函数，当该进程收到 SIGTERM 信号时，会在处理函数中清除临时文件以及释放其它资源，再而退出程序</u>。如果直接使用 SIGKILL 信号终止进程，从而跳过了 SIGTERM 信号的处理函数，通常 SIGKILL 终止进程是不友好的方式、是暴力的方式，这种方式应该作为最后手段，应首先尝试使用 SIGTERM，实在不行再使用最后手段 SIGKILL。

- SIGCHLD

当父进程的某一个子进程终止时，内核会向父进程发送该信号。当父进程的某一个子进程因收到信号而停止或恢复时，内核也可能向父进程发送该信号。注意这里说的停止并不是终止，你可以理解为暂停。该信号的系统默认操作是<b>忽略此信号</b>，如果父进程希望被告知其子进程的这种状态改变，则应捕获此信号。

- SIGCLD

与 SIGCHLD 信号同义。

- SIGCONT

将该信号发送给已停止的进程，进程将会恢复运行。<b>当进程接收到此信号时并不处于停止状态，系统默认操作是忽略该信号，但如果进程处于停止状态，则系统默认操作是使该进程继续运行。</b>

- SIGSTOP

这是一个“必停”信号，用于停止进程（注意停止不是终止，停止只是暂停运行、进程并没有终止），<b>应用程序无法将该信号忽略或者捕获，故而总能停止进程</b>。

- SIGTSTP

这也是一个停止信号，当用户在终端按下停止字符（通常是 CTRL + Z），那么系统会将 SIGTSTP 信号发送给前台进程组中的每一个进程，使其停止运行。

- SIGXCPU

当进程的 CPU 时间超出对应的资源限制时，内核将发送此信号给该进程。

- SIGVTALRM

应用程序调用 setitimer()函数设置一个虚拟定时器，当定时器定时时间到时，内核将会发送该信号给进程。

- SIGWINCH

在窗口环境中，当终端窗口尺寸发生变化时（譬如用户手动调整了大小，应用程序调用 ioctl()设置了大小等），系统会向前台进程组中的每一个进程发送该信号。

- SIGPOLL/SIGIO

这两个信号同义。这两个信号将会在高级 IO 章节内容中使用到，用于提示一个异步 IO 事件的发生，譬如应用程序打开的文件描述符发生了 I/O 事件时，内核会向应用程序发送 SIGIO 信号。

- SIGSYS

如果进程发起的系统调用有误，那么内核将发送该信号给对应的进程。

## 8.4 进程对信号的处理

<b>系统调用：</b>

- signal()
- sigaction()

### 8.4.1 signal()函数

``` c
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

！！！注！！！

> typedef void (*sighandler_t)(int)

表示定义了sighandler_t这种数据类型，它是指向函数的指针，所指向的函数接收int类型数据，返回值是void类型数据。

### 8.4.2 sigaction()函数

<b>系统调用</b>

更复杂，同时更具灵活性及移植性。

函数原型：

``` c
#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

<b>signum：</b>需要设置的信号。

<b>act：</b>指向sigaction结构体的指针。该参数不为NULL时，表示需要设置新的信号处理方式；为NULL时，表示无需修改该信号的处理方式。

<b>oldact：</b>指向sigaction结构体的指针。不为NULL时，将信号原本的处理方式通过该指针返回出来；为NULL时，不返回。

<b>返回值：</b>成功返回 0；失败将返回-1，并设置 errno。

``` c
struct sigaction
{
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};
```

<b>sa_handler：</b>指向信号处理函数的指针。

<b>sa_sigaction：</b>指向信号处理函数的指针。是一个替代的信号处理函数。sa_handler 和 sa_sigaction 是互斥的，不能同时设置。

<b>sa_flags：</b>控制信号处理过程的标志。可设置为：

- SA_NOCLDSTOP：如果signum为SIGCHLD，则子进程停止时或恢复时不会收到 SIGCHLD 信号。
- SA_NOCLDWAIT：如果 signum 是 SIGCHLD，则在子进程终止时不要将其转变为僵尸进程。
- SA_NODEFER：不要阻塞从某个信号自身的信号处理函数中接收此信号。
- SA_RESETHAND：执行完信号处理函数之后，将信号的处理方式设置为系统默认操作。
- SA_RESTART：被信号中断的系统调用，在信号处理完成之后将自动重新发起。
- SA_SIGINFO：如果设置了该标志，则表示使用 sa_sigaction 作为信号处理函数、而不是 sa_handler

siginfo_t 结构体：
``` c
siginfo_t
{
    int si_signo;       /* Signal number */
    int si_errno;       /* An errno value */
    int si_code;        /* Signal code */
    int si_trapno;      /* Trap number that caused hardware-generated signal(unused on most architectures) */
    pid_t si_pid;       /* Sending process ID */
    uid_t si_uid;       /* Real user ID of sending process */
    int si_status;      /* Exit value or signal */
    clock_t si_utime;   /* User time consumed */
    clock_t si_stime;   /* System time consumed */
    sigval_t si_value;  /* Signal value */
    int si_int;         /* POSIX.1b signal */
    void *si_ptr;       /* POSIX.1b signal */
    int si_overrun;     /* Timer overrun count; POSIX.1b timers */
    int si_timerid;     /* Timer ID; POSIX.1b timers */
    void *si_addr;      /* Memory location which caused fault */
    long si_band;       /* Band event (was int in glibc 2.3.2 and earlier) */
    int si_fd;          /* File descriptor */
    short si_addr_lsb;  /* Least significant bit of address(since Linux 2.6.32) */
    void *si_call_addr; /* Address of system call instruction(since Linux 3.5) */
    int si_syscall;     /* Number of attempted system call(since Linux 3.5) */
    unsigned int si_arch; /* Architecture of attempted system call(since Linux 3.5) */
}
```

## 8.5 向进程发送信号

本节介绍<b>系统调用</b>kill和<b>C库函数</b>raise函数。

### 8.5.1 kill函数

kill()系统调用可将信号发送给指定的进程或进程组中的每一个进程，其函数原型如下所示：

``` c
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
```

### 8.5.2 raise函数

有时进程需要向自身发送信号，<b>C库函数</b>raise()函数可用于实现这一要求，raise()函数原型如下所示：

``` c
#include <signal.h>
int raise(int sig);
```

## 8.6 alarm() 和 pause() 函数

<b>系统调用</b>

### 8.6.1 alarm()

函数原型：

``` c
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
```

### 8.6.2 pause()

函数原型：

``` c
#include <unistd.h>
int pause(void);
```

## 8.7 信号集

很多系统调用都使用到了信号集这种<u>数据类型</u>来作为参数传递。信号集其实就是 sigset_t 类型数据结构。

``` c
# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct
{
    unsigned long int __val[_SIGSET_NWORDS];
} sigset_t;
```

### 8.7.1 初始化信号集

``` c
#include <signal.h>
int sigemptyset(sigset_t *set); // 初始化空信号集
int sigfillset(sigset_t *set);  // 初始化包含所有信号的信号集
```

<b>set：</b>指向需要进行初始化的信号集变量。

### 8.7.2 向信号集中 添加/删除 信号

``` c
#include <signal.h>
int sigaddset(sigset_t *set, int signum);   // 添加信号
int sigdelset(sigset_t *set, int signum);   // 删除信号
```

### 8.7.3 测试信号是否在信号集中

``` c
#include <signal.h>
int sigismember(const sigset_t *set, int signum);
```

## 8.8 获取信号的描述信息

``` c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    printf("SIGINT 描述信息: %s\n", sys_siglist[SIGINT]);
    printf("SIGQUIT 描述信息: %s\n", sys_siglist[SIGQUIT]);
    printf("SIGBUS 描述信息: %s\n", sys_siglist[SIGBUS]);
    exit(0);
}
```

### 8.8.1 strsignal()函数

<b>C库函数</b>

``` c
#include <string.h>
char *strsignal(int sig);
```

### 8.8.2 psignal()函数

``` c
#include <signal.h>
void psignal(int sig, const char *s);
```

## 8.9 信号掩码（阻塞信号传递）

阻塞不代表忽略这个信号，而是等到“不阻塞”之后再处理这个信号。

一下函数可以设置当前进程的信号掩码（要阻塞信号的集合）。是<b>系统调用</b>

``` c
#include <signal.h>
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

## 8.10 阻塞等待信号sigsuspend()

要解决的问题：用sigprocmask函数将某信号加入掩码，以处理特定代码段，再将该信号移除掩码，调用pause函数等待之前阻塞的信号唤醒。若有信号在移除掩码信号和调用pause函数之间发生，则会跳转到信号处理函数，再返回主函数，进入pause，有违代码本意。

解决方法：将移除掩码信号和pause挂起进程这两个动作封装成一个原子操作，成为<b>系统调用</b>sigsuspend()

函数原型：

``` c
#include <signal.h>
int sigsuspend(const sigset_t *mask);
```

## 8.11 实时信号

### 8.11.1 sigpending()函数

将处于等待状态的信号放入set信号集。函数原型：

``` c
#include <signal.h>
int sigpending(sigset_t *set);
```

配合sigismember函数确定某信号是否在set信号集中，即确定某信号是否在等待信号中。

### 8.11.2 发送实时信号

## 8.12 异常退出abort()函数