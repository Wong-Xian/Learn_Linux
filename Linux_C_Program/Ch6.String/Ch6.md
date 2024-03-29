# Ch6 字符串处理

## 6.1 字符串输入输出

### 6.1.1 输出

常用的字符串输出函数有 putchar()、puts()、fputc()、fputs() 属于C库函数

#### 1、puts函数

puts()函数用来向标准输出设备（屏幕、显示器）输出字符串并自行换行。把字符串输出到标准输出设备，<font color=red>将'\0'转换为换行符'\n'，实现自动换行</font>。

函数原型：

``` c
#include <stdio.h>
int puts(const char *s);
```

<b>s：</b>需要进行输出的字符串。

<b>返回值：</b>成功返回一个非负数；失败将返回 EOF，EOF 其实就是-1。

#### 2、putchar函数

putchar()函数可以把参数 c 指定的字符（一个无符号字符）输出到标准输出设备，其输出可以是一个字符，可以是介于 0~127 之间的一个十进制整型数（包含 0 和 127，输出其对应的 ASCII 码字符），也可以是用 char 类型定义好的一个字符型变量。

函数原型：

``` c
#include <stdio.h>
int putchar(int c);
```

<font color=red>该函数输出字符后不会自动换行！</font>

#### 3、fputc函数

fputc()与 putchar()类似，也用于输出参数 c 指定的字符（一个无符号字符），与 putchar()区别在于，putchar()只能输出到标准输出设备，而 fputc()可把字符输出到指定的文件中，既可以是标准输出、标准错误设备，也可以是一个普通文件。

函数原型：

``` c
#include <stdio.h>
int fputc(int c, FILE *stream);
```

#### 4、fputs函数

同理，fputs()与 puts()类似，也用于输出一条字符串，与 puts()区别在于，puts()只能输出到标准输出设备，而 fputs()可把字符串输出到指定的文件中，既可以是标准输出、标准错误设备，也可以是一个普通文件。

函数原型：

``` c
#include <stdio.h>
int fputs(const char *s, FILE *stream);
```

### 6.1.2 输入

常用的字符串输入函数有 gets()、getchar()、fgetc()、fgets()，都是C库函数

#### 1、gets()函数

用于从标准输入设备（譬如键盘）中获取用户输入的字符串，函数原型：

``` c
#include <stdio.h>
char *gets(char *s);
```

gets()函数允许输入的字符串带有空格、制表符，输入的空格和制表符也是字符串的一部分，仅以回车换行符作为字符串的分割符。gets()会将回车换行符从输入缓冲区中取出来，然后将其丢弃。

scanf以%s格式输入的时候，空格、换行符、TAB 制表符等都是作为字符串分割符存在，即分隔符前后是两个字符串，读取字符串时并不会将分隔符读取出来作为字符串的组成部分。使用scanf()读走缓冲区中的字符串数据之后，缓冲区中依然还存在用户输入的分隔符。

#### 2、getchar()函数

用于从标准输入设备中读取一个字符（一个无符号字符），函数原型如下所示：

``` c
#include <stdio.h>
int getchar(void);
```

<b>返回值：</b>该函数以无符号 char 强制转换为 int 的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。

getchar()函数也是从输入缓冲区读取字符数据，但只读取一个字符，包括空格、TAB 制表符、换行回车符等。

#### 3、fgets()函数

函数原型：
``` c
#include <stdio.h>
char *fgets(char *s, int size, FILE *stream);
```

#### 4、fgetc()函数

函数原型：

``` c
#include <stdio.h>
int fgetc(FILE *stream);
```

<b>返回值：</b>该函数以无符号 char 强制转换为 int 的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。

## 6.2 字符串长度

计算字符串长度的C库函数strlen()函数原型：

``` c
#include <string.h>
size_t strlen(const char *s);
```

<b>s：</b>需要进行长度计算的字符串，字符串必须包含结束字符' \0 '。

<b>返回值：</b>返回字符串长度（以字节为单位），字符串结束字符' \0 '不计算在内。

## 6.3 字符串拼接

C 语言函数库中提供了 strcat()函数或 strncat()函数用于将两个字符串连接（拼接）起来，strcat 函数原型如下所示：

### 1、strcat()

``` c
#include <string.h>
char *strcat(char *dest, const char *src);
```

<b>dest：</b>目标字符串。

<b>src：</b>源字符串。

<b>返回值：</b>返回指向目标字符串 dest 的指针。

strcat()函数会把 src 所指向的字符串追加到 dest 所指向的字符串末尾，所以必须要保证 dest 有足够的存储空间来容纳两个字符串，否则会导致溢出错误；dest 末尾的'\0'结束字符会被覆盖，src 末尾的结束字符'\0'会一起被复制过去，最终的字符串只有一个'\0'。

### 2、strncat()

strncat()与 strcat()的区别在于，strncat 可以指定源字符串追加到目标字符串的字符数量，strncat 函数原型如下所示：

``` c
#include <string.h>
char *strncat(char *dest, const char *src, size_t n);
```

<b>n：</b>要追加的最大字符数。

## 6.4 字符串拷贝

C 语言函数库中提供了 strcpy()函数和 strncpy()函数用于实现字符串拷贝，strcpy 函数原型如下所示：

### 1、strcpy函数

``` c
#include <string.h>
char *strcpy(char *dest, const char *src);
```

作用：把src指向的字符串复制到dest指向的字符串。必须保证 dest 指向的内存空间足够大，能够容纳下 src 字符串，否则会导致溢出错误。

若dest中原本有数据，无论原本数据比src长或短，都会被src覆盖。

### 2、strncpy函数

strncpy()与 strcpy()的区别在于，strncpy()可以指定从源字符串 src 复制到目标字符串 dest 的字符数量，strncpy 函数原型如下所示：

``` c
#include <string.h>
char *strncpy(char *dest, const char *src, size_t n);
```

只将src的前n个字符替换掉dest的前n个字符，不覆盖dest其他的字符。

## 6.5 内存填充

将某一块内存的数据全部设置为指定的值（初始化时通常设置为0）

### 1、memset函数

函数原型：

``` c
#include <string.h>
void *memset(void *s, int c, size_t n);
```

### 2、bzero函数

将一段内存空间中的数据全部设置为 0

函数原型：

``` c
#include <strings.h>
void bzero(void *s, size_t n);
```

## 6.6 字符串比较

### 1、strcmp

函数原型：

``` c
#include <string.h>
int strcmp(const char *s1, const char *s2);
```

返回值：
- 如果返回值小于 0，则表示 str1 小于 str2
- 如果返回值大于 0，则表示 str1 大于 str2
- 如果返回值等于 0，则表示字符串 str1 等于字符串 str2

根据ASCII码值依次比较 str1 和 str2 的每一个字符，直到出现了不同的字符，或者某一字符串已经到达末尾。

### 2、strncmp

函数原型：

``` c
#include <string.h>
int strncmp(const char *s1, const char *s2, size_t n);
```

<b>n：</b>最多比较前 n 个字符。

## 6.7 字符串查找

### 1、strchr函数

函数原型：

``` c
#include <string.h>
char *strchr(const char *s, int c);
```

### 2、strrchr函数

与上一个函数的不同，是从后往前查找字符。

### 3、strstr函数

在字符串中找“子字符串”第一次出现的位置。

## 6.8 字符串与数字互转

### 6.8.1 字符串->整型数据

#### atoi、atol、atoll 函数

函数原型：

``` c
// 作用：将字符串形式的数字，转换成整型等数据类型的数字。
#include <stdlib.h>

int atoi(const char *nptr);         // 字符串转换成int
long atol(const char *nptr);        // 字符串转换成long
long long atoll(const char *nptr);  // 字符串转换成long long
```

#### strtol、strtoll 函数

strtol()、strtoll()可以实现将多种不同进制数（譬如二进制表示的数字字符串、八进制表示的数字字符串、十六进制表示的数数字符串）表示的字符串转换为整形数据。函数原型：

``` c
#include <stdlib.h>
long int strtol(const char *nptr, char **endptr, int base);
long long int strtoll(const char *nptr, char **endptr, int base);
```

<b>endptr：</b>char **类型的指针。<font color=red>由于char类型数组，其变量名本身就是一个指针，所以“*变量名”相当于char的二级指针。</font>

- 不为NULL时：函数将字符串中第一个无效字符的地址存储在* endptr 中。如果根本没有数字，函数会将 nptr 的原始值存储在* endptr 中（并返回 0）。

- 为NULL时：表示不接收相应信息。

<b>base：</b>数字基数，数字进制数。介于2到36之间。（z代表35）在 base=0 的情况下，如果字符串包含一个了“0x”前缀，表示该数字将以 16 为基数；如果包含的是“0”前缀，表示该数字将以 8 为基数。

#### strtoul、strtoull 函数

strtoul()返回值类型是 unsigned long int，strtoull()返回值类型是 unsigned long long int，函数原型如下所示：

``` c
#include <stdlib.h>
unsigned long int strtoul(const char *nptr, char **endptr, int base);
unsigned long long int strtoull(const char *nptr, char **endptr, int base);
```

### 6.8.2 字符串->浮点型数据

C 函数库中用于字符串转浮点型数据的函数有 atof()、strtod()、strtof()、strtold()。

#### atof 函数

将字符串转换为一个 double 类型的浮点数据

``` c
#include <stdlib.h>
double atof(const char *nptr);
```

#### strtod、strtof、strtold 函数

strtof()、strtod()以及 strtold()三个库函数可分别将字符串转换为 float 类型数据、double 类型数据、long double 类型数据，函数原型如下所示：

``` c
#include <stdlib.h>
double strtod(const char *nptr, char **endptr);
float strtof(const char *nptr, char **endptr);
long double strtold(const char *nptr, char **endptr);
```

### 6.8.3 数字->字符串

数字转换为字符串推荐大家使用前面介绍的格式化 IO 相关库函数，譬如使用 printf()将数字转字符串、并将其输出到标准输出设备或者使用 sprintf()或 snprintf()将数字转换为字符串并存储在缓冲区中

## 6.9 给应用程序传参

可以直接向main函数传参，运行编译好的二进制文件时，

## 6.10 正则表达式

正则表达式，又称为规则表达式（英语: Regular Expression）

?通配符匹配 0 个或 1 个字符

*通配符匹配 0 个或多个字符

正则表达式其实也是一个字符串，该字符串由普通字符（譬如，数字 0~9、大小写字母以及其它字符）和特殊字符（称为“元字符”）所组成，由这些字符组成一个“规则字符串”，这个“规则字符串”用来表达对给定字符串的一种查找、匹配逻辑。

## 6.11 C语言中使用正则表达式

略