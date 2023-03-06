#include<stdio.h>
#include<stdlib.h>

int main()
{
    // define var
    FILE* fp;
    char buf[]="hello world!\nhello world again!\n";
    char bufout[100]={0};
    int size;

    // open file
    if (NULL == (fp=fopen("./test_file", "w+")))
    {
        perror("fopen error");
        exit(-1);
    }

    // set buf
    if (0 != setvbuf(fp, buf, _IONBF, 1024))    // 此时忽略buf和1024
    {
        perror("setvbuf error");
        fclose(fp);
        exit(-1);
    }

    // write data
    if (sizeof(buf)>fwrite(buf, 1, sizeof(buf), fp))
    {
        perror("fwrite error");
        fclose(fp);
        exit(-1);
    }

    // reset buf
    if (0 != setvbuf(fp, buf, _IOLBF, 1024))// 每次换行，将stdio缓冲区数据提交到内核缓冲区
    {
        perror("setvbuf error");
        fclose(fp);
        exit(-1);
    }

    // write data
    if (sizeof(buf)>fwrite(buf, 1, sizeof(buf), fp))
    {
        perror("fwrite error");
        fclose(fp);
        exit(-1);
    }

    // reset buf
    if (0 != setvbuf(fp, buf, _IOFBF, 1024))// 填满stdio缓冲区才将数据提交到内核缓冲区
    {
        perror("setvbuf error");
        fclose(fp);
        exit(-1);
    }
    
    // write data
    if (sizeof(buf)>fwrite(buf, 1, sizeof(buf), fp))
    {
        perror("fwrite error");
        fclose(fp);
        exit(-1);
    }

    // set cursor
    if (-1==fseek(fp, 0,SEEK_SET))
    {
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }

    // read data
    if (32*3>(size=fread(bufout, 1, 32*3, fp)))
    {
        if (feof(fp))
        {
            printf("reach the end of file!\n");
        }
        else
        {
            perror("fread error");
            fclose(fp);
            exit(-1);
        }
    }
    printf("读取了%d个字节，内容如下：\n%s", size, bufout);

    // close file
    fclose(fp);
    exit(0);

}