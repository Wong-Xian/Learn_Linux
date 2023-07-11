#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    FILE *fp = NULL;
    char rd_buf[100] = {0};
    char wr_buf[] = "正点原子 http://www.openedv.com/forum.php\n";
    int ret;


    /* 打开文件 */
    if (NULL == (fp = fopen("./test_file", "w+")))
    {
        perror("fopen error");
        exit(-1);
    }
    printf("文件打开成功!\n");
    
    
    /* 写文件 */
    if (sizeof(wr_buf) > fwrite(wr_buf, 1, sizeof(wr_buf), fp))
    {
        printf("fwrite error\n");
        fclose(fp);
        exit(-1);
    }
    printf("数据写入成功!\n");
    
    /* 将读写位置移动到文件头部 */
    if (0 > fseek(fp, 0, SEEK_SET))
    {
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }
    
    /* 读文件 */
    if (sizeof(wr_buf) > (ret = fread(rd_buf, 1, sizeof(wr_buf), fp)))
    {
        printf("fread error\n");
        fclose(fp);
        exit(-1);
    }
    printf("成功读取%d 个字节数据: %s\n", ret, rd_buf);
    
    
    /* 关闭文件 */
    fclose(fp);
    exit(0);
}