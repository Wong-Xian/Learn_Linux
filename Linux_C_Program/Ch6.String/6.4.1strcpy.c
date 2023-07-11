#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char str1[5] = {0};
    char str2[50] = "hahahahahahahahahahaha! ";
    char str3[] = "Hello World!";

    strcpy(str1, str3); // str1是空的
    strcpy(str2, str3); // str2非空

    puts(str1);
    puts(str2);
    puts(str3);

    exit(0);
}

/*
Sum
现象：
    str1数组长度小于str3字符串长度。当用strcpy函数把str3拷贝到str1后，通过puts函数，依旧能完整输出拷贝的内容，此时调用sizeof函数查看str1的大小，仍然是初始化时设定的数组长度。
解释：
    首先，strcpy函数不会改变数组的长度，str1的长度仍然是5。
    其次，puts函数只在遇到'\0'符号时结束输出，并不是根据数组长度来决定是否结束输出的。
结论：
    dest指向的数组长度小于src字符串长度时，也能正常调用strcpy函数，只是超过dest数组长度的部分在内存空间上，继续存储在dest数组的后面，但其内容不属于dest数组了。
*/