# CH9 进程

## 9.1 进程 与 程序

### 9.1.1 main()函数由谁调用

运行 main()函数之前需要先执行一段引导代码，最终由这段引导代码去调用应用程序的 main()函数。

程序运行需要通过操作系统的加载器来实现，加载器是操作系统中的程序，当执行程序时，加载器负责将此应用程序加载内存中去执行。

执行带参数的main函数：命令行参数（command-line argument）由 shell 进程逐一进行解析，shell 进程会将这些参数传递给加载器，加载器加载应用程序时会将其传递给应用程序引导代码，当引导程序调用 main()函数时，在由它最终传递给 main()函数。

### 9.1.2 程序如何结束

1. 正常终止
    1. return
    2. C库函数exit()
    3. 系统调用_exit(),_Exit()
2. 异常终止
    1. abort()函数
    2. 收到信号，如SIGKILL

atexit()库函数用于注册一个进程在正常终止时要调用的函数。

函数原型：

``` c
#include <stdlib.h>
int atexit(void (*function)(void));
```

### 9.1.3 何为进程

进程其实就是一个可执行程序的实例。

可执行程序的实例就是可执行文件被运行。

进程是一个动态过程，而非静态文件，它是程序的一次运行过程，当应用程序被加载到内存中运行之后它就称为了一个进程，当程序运行结束后也就意味着进程终止，这就是进程的一个生命周期。

### 9.1.4 进程号

PID 唯一标识进程 是一个正数

<b>系统调用</b>getpid()函数用于获取当前进程的PID

原型：

``` c
#include <sys/types.h>
#include <unistd.h>
pid_t getpid(void);
```

<b>系统调用</b>getppid()函数用于获取父进程的PID

原型：

``` c
#include <sys/types.h>
#include <unistd.h>
pid_t getppid(void);
```

## 9.2 进程的环境变量

在终端通过env查询

### 9.2.1 应用程序中获取环境变量

进程的环境变量是从其父进程中继承过来的。

环境变量的字符信息存放在字符串数组中，全局变量environ变量指向环境变量。

``` c
extern char **environ;
```

获取指定环境变量，用C库函数，getenv()函数

### 9.2.2 添加/删除/修改 环境变量

1. putenv()

``` c
#include <stdlib.h>
int putenv(char *string);
```

string不能是栈中分配的数组，即需要用户手动开辟内存空间。

2. setenv()

``` c
#include <stdlib.h>
int setenv(const char *name, const char *value, int overwrite);
```

3. unsetenv()

``` c
#include <stdlib.h>
int unsetenv(const char *name);
```

### 9.2.3 清空环境变量

``` c
#include <stdlib.h>
int clearenv(void);
```

### 9.2.4 环境变量的作用

告诉机器，你输入的命令到哪里去执行。指定命令执行的路径。

## 9.3 进程的内存布局

C程序的组成部分：
1. 正文段，代码段
2. 初始化数据段
3. 未初始化数据段（bss）
4. 栈
   1. 程序的局部变量
   2. 函数调用时保存的信息
5. 堆

## 9.4 进程的虚拟地址空间

每个进程都在自己独立的地址空间运行。

32位系统中，每个进程的地址空间为4GB，其中用户独享3GB，内核独享1GB。

硬件MMU将虚拟地址和物理地址形成映射关系。

引入虚拟内存解决物理上内存隔离的问题，不用考虑链接地址和运行地址不统一的问题

## 9.5 fork()创建子进程

``` c
#include <unistd.h>
pid_t fork(void);
```

调用后产生子进程，其与父进程之间的关系，共用代码段，但不共用数据段、堆、栈等。

## 9.6 父、子进程之间的文件共享

fork后，子进程获得父进程所有文件描述符的副本，意味着父、子进程对应的文件描述符均指向相同的文件表。如果子进程更新了文件偏移量，那么这个改变也会影响到父进程中相应文件描述符的位置偏移量。

测试了在fork函数之前打开文件，在父子进程中分别对文件进行编辑的情况；也测试了在fork函数之后，父子进程中分别打开同一个文件进行编辑的情况。

## 9.7 系统调用vfork()

<b>系统调用</b>

函数原型：

``` c
#include <sys/types.h>
#include <unistd.h>
pid_t vfork(void);
```

fork() 与 vfork()的区别：

1. 执行次序
   1. fork()： 父子进程的执行次序不确定。
   2. vfork()：保证子进程先运行,在它调用 exec（进程替换） 或 exit（退出进程）之后父进程才可能被调度运行。

2. 地址空间
   1. fork()： 子进程拷贝父进程的地址空间，子进程是父进程的一个复制品。
   2. vfork()：子进程共享父进程的地址空间（准确来说，在调用 exec（进程替换） 或 exit（退出进程） 之前与父进程数据是共享的）


## 9.8 fork()之后的竞争条件

调用fork函数后产生了子进程。无法确定父子两个进程谁先访问CPU，也即无法确定两个进程谁先继续运行。

方法：对父进程绑定信号处理函数，然后在创建完子进程后挂起父进程。在子进程执行完后向父进程发送特定信号。达到先执行子进程，后执行父进程的效果。

## 9.9 进程的诞生与终止

### 9.9.1 进程的诞生

Linux下所有进程都由父进程创建而来。

所有进程的父进程是PID为1的init进程，它是Linux系统内核运行的第一个进程。

### 9.9.2 进程的终止

分为 正常终止 和 异常终止。

exit()函数包括以下步骤：
1. 如果程序中注册了进程终止处理函数，那么会调用终止处理函数
2. 刷新 stdio 流缓冲区
3. 执行_exit()系统调用

解释了为什么前面的例子中，子进程调用_exit()，而父进程调用exit()。因为子进程产生时复制了父进程中的各种数据（包括stdio缓冲流），如果调用exit()会导致子进程的stdio缓冲空间被刷新，而调用_exit()则不会刷新。

## 9.10 监视子进程

### 9.10.1 wait()函数

系统调用 wait()可以等待进程的任一子进程终止，同时获取子进程的终止状态信息。还有一个功能，回收子进程的一些资源，俗称为子进程“收尸”。

``` c
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
```

### 9.10.2 waitpid()函数

``` c
#include <sys/types.h>
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *status, int options);
```

### 9.10.3 waitid()函数

略

### 9.10.4 僵尸进程 与 孤儿进程

- 孤儿进程

父进程比子进程先结束。孤儿进程自动变为init进程的子进程，此时其父进程pid为1。

- 僵尸进程

子进程结束，父进程未对其进行资源回收时，该进程称为僵尸进程。

### 9.10.5 SIGCHLD信号

- 当父进程的某个子进程终止时，父进程会收到 SIGCHLD 信号
- 当父进程的某个子进程因收到信号而停止（暂停运行）或恢复时，内核也可能向父进程发送该信号

存在问题：在父进程收到SIGCHLD信号，调用信号处理函数为子进程“收尸”时，若又有子进程终止，则无法再次触发“收尸”过程。

解决方法：在信号处理函数中加入如下代码段，若子进程状态发生变化，waitpid函数返回子进程PID，进入while循环，直到子进程状态无变化，waitpid函数返回0时，才离开while循环。

``` c
while (waitpid(-1, NULL, WNOHANG) > 0)
   continue;
```

## 9.11 执行新程序


### 9.11.1 execve函数

<b>系统调用</b>函数原型：

``` c
#include <unistd.h>
int execve(const char *filename, char *const argv[], char *const envp[]);
```

execve 调用成功将不会返回；失败将返回-1，并设置 errno。

当 newApp 程序运行完成退出后，testApp 进程就结束了。

### 9.11.2 exec库函数

<b>C库函数</b>函数原型：

``` c
#include <unistd.h>

extern char **environ;

int execl   (const char *path, const char *arg, ... /* (char *) NULL */);
int execlp  (const char *file, const char *arg, ... /* (char *) NULL */);
int execle  (const char *path, const char *arg, ... /*, (char *) NULL, char * const envp[] */);

int execv   (const char *path, char *const argv[]);
int execvp  (const char *file, char *const argv[]);
int execvpe (const char *file, char *const argv[], char *const envp[]);
```

### 9.11.3 exec族函数使用示例

略

### 9.11.4 system函数

使用 system()函数可以很方便地在我们的程序当中执行任意 shell 命令。

``` c
#include <stdlib.h>
int system(const char *command);
```

## 9.12 进程状态与进程关系

### 9.12.1 进程状态

- 就绪态（Ready）
- 运行态
- 僵尸态
- 等待态
  - 可中断睡眠状态
  - 不可中断睡眠状态
- 暂停态

### 9.12.2 进程关系

1. 无关系
2. 父子进程关系
3. 进程组

获取进程对应的进程组的id，函数原型：

``` c
#include <unistd.h>
pid_t getpgid(pid_t pid);
pid_t getpgrp(void);
```

加入一个现有的进程组或创建一个新的进程组。函数原型：

``` c
#include <unistd.h>
int setpgid(pid_t pid, pid_t pgid);
int setpgrp(void);
```

4. 会话

会话是一个或多个进程组的集合，有一个前台进程组和一个或多个后台进程组。每个会话有个Leader，即创建会话的进程。

会话的Leader与终端连接后，该终端成为会话的控制终端，Leader成为控制进程。

查询会话ID的函数，是系统调用，原型如下：

``` c
#include <unistd.h>
pid_t getsid(pid_t pid);
```

系统调用setsid，用于创建会话，函数原型：

``` c
#include <unistd.h>
pid_t setsid(void);
```

## 9.13 守护进程

### 9.13.1 何为守护进程

运行在后台的特殊进程，独立于控制终端，周期性地执行某项任务，或等待某些事件的产生。

特点：
- 长期运行
- 与控制终端脱离

### 9.13.2 编写守护进程程序

1. 创建子进程、终止父进程
2. 子进程调用 setsid 创建会话
3. 将工作目录更改为根目录
4. 重设文件权限掩码 umask
5. 关闭不再需要的文件描述符
6. 将文件描述符号为 0、1、2 定位到/dev/null
7. 其它：忽略 SIGCHLD 信号

### 9.13.3 SIGHUP信号

当用户准备退出会话时，系统向该会话发出 SIGHUP 信号，会话将 SIGHUP 信号发送给所有子进程，子进程接收到 SIGHUP 信号后，便会自动终止，当所有会话中的所有进程都退出时，会话也就终止了。

## 9.14 单例模式运行

程序只能被执行一次，只要该程序没有结束，就无法再次运行，我们把这种情况称为单例模式运行。