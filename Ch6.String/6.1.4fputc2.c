#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = NULL;

    /* 创建一个文件 */
    fp = fopen("./new_file", "a");
    if (NULL == fp)
    {
        perror("fopen error");
        exit(-1);
    }

    /* 输入字符到文件 */
    fputc('A', fp);
    fputc('B', fp);
    fputc('C', fp);
    fputc('D', fp);
    fputc('\n', fp);

    /* 关闭文件 */
    fclose(fp);
    exit(0);
}