#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buf[] = "Hello World!\n";
    FILE *fp = NULL;
    
    /* 打开文件 */
    if (NULL == (fp = fopen("./test_file", "w")))
    {
        perror("fopen error");
        exit(-1);
    }
    printf("文件打开成功!\n");
    
    /* 写入数据 */
    if (sizeof(buf) > fwrite(buf, 1, sizeof(buf), fp))
    {
        printf("fwrite error\n");
        fclose(fp);
        exit(-1);
    }
    printf("数据写入成功!\n");

    /* 关闭文件 */
    fclose(fp);
    exit(0);
}