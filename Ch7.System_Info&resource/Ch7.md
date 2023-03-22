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

jiffies 是内核中定义的一个全局变量。内核使用 jiffies 来记录系统从启动以来的系统节拍数。

节拍率越高，每一个节拍时间越短，记录的时间精度越高。高节拍率会导致系统中断的产生更加频繁，频繁的中断会加剧系统的负担。

### 7.2.3 获取时间time/gettimeofday

#### 1、time

系统调用 time()用于获取当前时间，以秒为单位，返回得到的值是自 1970-01-01 00:00:00 +0000 (UTC)以来的秒数，其函数原型如下所示：

``` c
#include <time.h>
time_t time(time_t *tloc);
```

如果 tloc 参数不是 NULL，则返回值存储在 tloc 指向的内存中。

成功则返回自 1970-01-01 00:00:00 +0000 (UTC)以来的时间值（以秒为单位）；失败则返回-1，并会设置 errno。

#### 2、gettimeofday

time()获取到的时间只能精确到秒，如果想要获取更加精确的时间可以使用系统调用 gettimeofday 来实现，gettimeofday()函数提供微秒级时间精度，函数原型如下所示:

``` c 
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz);
```

### 7.2.4 时间转换函数

把上一节中的函数获取到的时间值转换成方便人来查看的形式。

#### 1、ctime函数

<b>C 库函数</b>

可以将日历时间转换为可打印输出的字符串形式。

函数原型：

``` c
#include <time.h>
char* ctime(const time_t *timep);
char* ctime_r(const time_t *timep, char *buf);
```

#### 2、localtime函数

<b>C 库函数</b>

localtime()函数可以把 time()或 gettimeofday()得到的秒数（time_t 时间或日历时间）变成一个 struct tm结构体所表示的时间，该时间对应的是本地时间。

函数原型：

``` c
#include <time.h>
struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *timep, struct tm *result);

struct tm
{
    int tm_sec; /* 秒(0-60) */
    int tm_min; /* 分(0-59) */
    int tm_hour; /* 时(0-23) */
    int tm_mday; /* 日(1-31) */
    int tm_mon; /* 月(0-11) */
    int tm_year; /* 年(这个值表示的是自 1900 年到现在经过的年数) */
    int tm_wday; /* 星期(0-6, 星期日 Sunday = 0、星期一=1…) */
    int tm_yday; /* 一年里的第几天(0-365, 1 Jan = 0) */
    int tm_isdst; /* 夏令时 */
};
```

#### 3、gmtime函数

<b>C 库函数</b>

gmtime()函数也可以把 time_t 时间变成一个 struct tm 结构体所表示的时间，与 localtime()所不同的是，<b>gmtime()函数所得到的是 UTC 国际标准时间，</b>并不是计算机的本地时间，这是它们之间的唯一区别。

``` c
#include <time.h>
struct tm *gmtime(const time_t *timep);
struct tm *gmtime_r(const time_t *timep, struct tm *result);
```

#### 4、mktime函数

<b>C 库函数</b>

mktime()函数与 localtime()函数相反，mktime()可以将使用 struct tm 结构体表示的分解时间转换为 time_t时间（日历时间）。

函数原型：

``` c
#include <time.h>
time_t mktime(struct tm *tm);
```

成功返回转换得到 time_t 时间值；失败返回-1。

#### 5、asctime函数

<b>C 库函数</b>

asctime()函数与 ctime()函数的作用一样，也可将时间转换为可打印输出的字符串形式，与 ctime()函数的区别在于，ctime()是将 time_t 时间转换为固定格式字符串、而 asctime()则是将 struct tm 表示的分解时间转换为固定格式的字符串。

#### 6、strftime函数

<b>C 库函数</b>

此函数也可以将一个 struct tm 变量表示的分解时间转换为为格式化字符串，并且在功能上比 asctime()和 ctime()更加强大，它可以根据自己的喜好自定义时间的显示格式。

函数原型：

``` c
#include <time.h>
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
```

s：指向一个缓存区的指针，该缓冲区用于存放生成的字符串。

max：字符串的最大字节数。

### 7.2.5 设置时间 settimeofday

<b>系统调用</b>

设置系统的本地时间

函数原型：

``` c
#include <sys/time.h>
int settimeofday(const struct timeval *tv, const struct timezone *tz);
```

tz应设置为NULL


## 7.3 进程时间

进程时间指的是进程从创建后（也就是程序运行后）到目前为止这段时间内使用 CPU 资源的时间总数。由两部分组成

- 用户 CPU 时间：进程在用户空间（用户态）下运行所花费的 CPU 时间。有时也称为虚拟时间（virtual time）。
- 系统 CPU 时间：进程在内核空间（内核态）下运行所花费的 CPU 时间。这是内核执行系统调用或代表进程执行的其它任务（譬如，服务页错误）所花费的时间。

一般来说，进程时间指的是用户 CPU 时间和系统 CPU 时间的总和，也就是总的 CPU 时间。

### 7.3.1 times函数

times()函数用于获取当前进程时间，其函数原型如下所示：

``` c
#include <sys/times.h>
clock_t times(struct tms *buf);

struct tms
{
    clock_t tms_utime; /* user time, 进程的用户 CPU 时间, tms_utime 个系统节拍数 */
    clock_t tms_stime; /* system time, 进程的系统 CPU 时间, tms_stime 个系统节拍数 */
    clock_t tms_cutime; /* user time of children, 已死掉子进程的 tms_utime + tms_cutime 时间总和 */
    clock_t tms_cstime; /* system time of children, 已死掉子进程的 tms_stime + tms_cstime 时间总和 */
};
```

### 7.3.2 clock函数

库函数 clock()提供了一个更为简单的方式用于获取进程时间，它的返回值描述了进程使用的总的 CPU 时间（也就是进程时间，包括用户 CPU 时间和系统 CPU 时间），其函数原型如下所示：

``` c
#include <time.h>
clock_t clock(void);
```

## 7.4 产生随机数

学习生成随机数

有 随机数 & 伪随机数 之分

### 1、rand函数

``` c
#include <stdlib.h>
int rand(void);
```

问题：就是每一次运行程序所得到的随机数序列都是相同的。解决方法：可通过 srand()设置随机数种子。

### 2、srand函数

``` c
#include <stdlib.h>
void srand(unsigned int seed);
```

常用方法：srand(time(NULL));

## 7.5 休眠

有时需要将进程暂停或休眠一段时间，进入休眠状态之后，程序将暂停运行，直到休眠结束。常用的系统调用和 C 库函数有 sleep()、usleep()以及 nanosleep()，这些函数在应用程序当中通常作为延时使用，譬如延时 1 秒钟，本小节将一一介绍。

### 7.5.1 秒级休眠sleep

<b>C库函数</b>

函数原型：

``` c
#include <unistd.h>
unsigned int sleep(unsigned int seconds);
```

### 7.5.2 微秒级休眠usleep

<b>C库函数</b>

函数原型：

``` c
#include <unistd.h>
int usleep(useconds_t usec);
```

<b>usec：</b>休眠时长，以微秒为单位。

成功返回0，错误返回-1，并设置 errno。

### 7.5.3 高精度休眠nanosleep

<b>Linux系统调用</b>

nanosleep()具有更高精度来设置休眠时间长度，支持纳秒级时长设置。

``` c
#include <time.h>
int nanosleep(const struct timespec *req, struct timespec *rem);
```

## 7.6 申请堆内存

### 7.6.1 在堆上分配内存 malloc和free

malloc函数原型：

``` c
#include <stdlib.h>
void *malloc(size_t size);
```

size：需要分配的内存大小，以字节为单位。

void* 表示返回值指向的类型未定，常需要做强制类型转换。

需要对malloc分配的堆内存进行初始化操作，再使用。

用完内存后需要手动释放，用free函数，函数原型：

``` c
#include <stdlib.h>
void free(void *ptr);
```

ptr：指向需要被释放的堆内存对应的指针。

### 7.6.2 在堆上分配内存的其他方法

### 7.6.3 分配对齐内存

## 7.7 proc文件系统