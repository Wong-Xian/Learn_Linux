# Ch7 系统信息与系统资源

## 7.1 系统信息

### 7.1.1 系统标识uname

系统调用 uname()用于获取有关当前操作系统内核的名称和信息

``` c
#include <sys/utsname.h>
int uname(struct utsname *buf);

struct utsname      // 结构体
{
    char sysname[]; /* 当前操作系统的名称 */
    char nodename[]; /* 网络上的名称（主机名） */
    char release[]; /* 操作系统内核版本 */
    char version[]; /* 操作系统发行版本 */
    char machine[]; /* 硬件架构类型 */
    #ifdef _GNU_SOURCE
        char domainname[];/* 当前域名 */
    #endif
};
```

<b>buf：</b>struct utsname 结构体类型指针，指向一个 struct utsname 结构体类型对象。

<b>返回值：</b>成功返回 0；失败将返回-1，并设置 errno。

### 7.1.2 sysinfo函数

sysinfo 系统调用可用于获取一些系统统计信息。

``` c
#include <sys/sysinfo.h>
int sysinfo(struct sysinfo *info);

struct sysinfo
{
    long uptime; /* 自系统启动之后所经过的时间（以秒为单位） */
    unsigned long loads[3]; /* 1, 5, and 15 minute load averages */
    unsigned long totalram; /* 总的可用内存大小 */
    unsigned long freeram; /* 还未被使用的内存大小 */
    unsigned long sharedram; /* Amount of shared memory */
    unsigned long bufferram; /* Memory used by buffers */
    unsigned long totalswap; /* Total swap space size */
    unsigned long freeswap; /* swap space still available */
    unsigned short procs; /* 系统当前进程数量 */
    unsigned long totalhigh; /* Total high memory size */
    unsigned long freehigh; /* Available high memory size */
    unsigned int mem_unit; /* 内存单元大小（以字节为单位） */
    char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding to 64 bytes */
};
```

### 7.1.3 gethostname函数

此函数可用于单独获取 Linux 系统主机名，与 struct utsname 数据结构体中的 nodename 变量一样。

``` c
#include <unistd.h>
int gethostname(char *name, size_t len);
```

<b>name：</b>指向用于存放主机名字符串的缓冲区。

<b>len：</b>缓冲区长度。

<b>返回值：</b>成功返回 0,；失败将返回-1，并会设置 errno。

### 7.1.4 sysconf函数

sysconf()函数是一个库函数，可在运行时获取系统的一些配置信息，譬如页大小（page size）、主机名的最大长度、进程可以打开的最大文件数、每个用户 ID 的最大并发进程数等。

``` c
#include <unistd.h>
long sysconf(int name);
```

调用 sysconf()函数获取系统的配置信息，参数 name 指定了要获取哪个配置信息，参数 name 可取以下任何一个值。

- _SC_ARG_MAX：exec 族函数的参数的最大长度，exec 族函数后面会介绍，这里先不管！
- _SC_CHILD_MAX：每个用户的最大并发进程数，也就是同一个用户可以同时运行的最大进程数。
- _SC_HOST_NAME_MAX：主机名的最大长度。
- _SC_LOGIN_NAME_MAX：登录名的最大长度。
- _SC_CLK_TCK：每秒时钟滴答数，也就是系统节拍率。
- _SC_OPEN_MAX：一个进程可以打开的最大文件数。
- _SC_PAGESIZE：系统页大小（page size）。
- _SC_TTY_NAME_MAX：终端设备名称的最大长度。

用的比较多的是_SC_PAGESIZE 和_SC_CLK_TCK，在后面章节示例代码中有使用到。

若指定的参数 name 为无效值，则 sysconf()函数返回-1，并会将 errno 设置为 EINVAL。否则返回的值便是对应的配置值。注意，返回值是一个 long 类型的数据。

## 7.2 时间、日期

### 7.2.1 时间的概念

GMT时间 -> Greenwich Mean Time

UTC时间 -> Coordinated Universal Time

时区的概念

在 Ubuntu 系统下，时区信息通常以标准格式保存在一些文件当中，这些文件通常位于/usr/share/zoneinfo目录下。

系统的本地时间由时区配置文件/etc/localtime 定义，通常链接到/usr/share/zoneinfo 目录下的某一个文件。

### 7.2.2 Linux系统中的时间

#### 点时间 和 段时间

也就是一个时间点 和 一段时间

#### 实时时钟RTC

操作系统的两个时钟

- 系统时钟System Clock 内核维护，关机即无。
- 实时时钟Real Time Clock 时钟芯片提供，专门电池供电，关机状态下继续计时。

#### Linux 系统如何记录时间

Linux 系统在开机启动之后首先会读取 RTC 硬件获取实时时钟作为系统时钟的初始值，之后内核便开始维护自己的系统时钟。所以由此可知，RTC 硬件只有在系统开机启动时会读取一次，目的是用于对系统时钟进行初始化操作，之后的运行过程中便不会再对其进行读取操作了。

而在系统关机时，内核会将系统时钟写入到 RTC 硬件，以进行同步操作。

#### jiffies 的引入

## 7.3 进程时间

## 7.4 产生随机数

## 7.5 休眠

## 7.6 申请堆内存

## 7.7 proc文件系统