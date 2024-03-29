#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>

/**** BMP 文件头数据结构 ****/
typedef struct {
    unsigned char type[2]; //文件类型
    unsigned int size; //文件大小
    unsigned short reserved1; //保留字段 1
    unsigned short reserved2; //保留字段 2
    unsigned int offset; //到位图数据的偏移量
} __attribute__ ((packed)) bmp_file_header;


/**** 位图信息头数据结构 ****/
typedef struct {
    unsigned int size; //位图信息头大小
    int width; //图像宽度
    int height; //图像高度
    unsigned short planes; //位面数
    unsigned short bpp; //像素深度
    unsigned int compression; //压缩方式
    unsigned int image_size; //图像大小
    int x_pels_per_meter; //像素/米
    int y_pels_per_meter; //像素/米
    unsigned int clr_used;
    unsigned int clr_omportant;
} __attribute__ ((packed)) bmp_info_header;


/**** 静态全局变量 ****/
static int width; //LCD X 分辨率
static int height; //LCD Y 分辨率
static unsigned short *screen_base = NULL; //映射后的显存基地址
static unsigned long line_length; //LCD 一行的长度（字节为单位）


/********************************************************************
* 函数名称： show_bmp_image
* 功能描述： 在 LCD 上显示指定的 BMP 图片
* 输入参数： 文件路径
* 返 回 值： 成功返回 0, 失败返回-1
********************************************************************/
static int show_bmp_image(const char *path)
{
    bmp_file_header file_h;
    bmp_info_header info_h;
    unsigned short *line_buf = NULL; //行缓冲区
    unsigned long line_bytes; //BMP 图像一行的字节的大小
    unsigned int min_h, min_bytes;
    int fd_BMP = -1;
    int j;


    /* 打开文件 */
    if (0 > (fd_BMP = open(path, O_RDONLY)))
    {
        perror("open error");
        return -1;
    }

    /* 读取 BMP 文件头 */
    if (sizeof(bmp_file_header) != read(fd_BMP, &file_h, sizeof(bmp_file_header)))
    {
        perror("read error");
        close(fd_BMP);
        return -1;
    }
    if (0 != memcmp(file_h.type, "BM", 2))
    {
        fprintf(stderr, "it's not a BMP file\n");
        close(fd_BMP);
        return -1;
    }
    
    /* 读取位图信息头 */
    if (sizeof(bmp_info_header) != read(fd_BMP, &info_h, sizeof(bmp_info_header)))
    {
        perror("read error");
        close(fd_BMP);
        return -1;
    }

    /* 打印信息 */
    printf("文件大小: %d\n"
    "位图数据的偏移量: %d\n"
    "位图信息头大小: %d\n"
    "图像分辨率: %d*%d\n"
    "像素深度: %d\n",
    file_h.size, file_h.offset, info_h.size, info_h.width, info_h.height, info_h.bpp);


    /* 将文件读写位置移动到图像数据开始处 */
    if (-1 == lseek(fd_BMP, file_h.offset, SEEK_SET))
    {
        perror("lseek error");
        close(fd_BMP);
        return -1;
    }


    /* 申请一个 buf、暂存 bmp 图像的一行数据 */
    line_bytes = info_h.width * info_h.bpp / 8; // 计算【图片】一行数据的大小，单位字节
    line_buf = malloc(line_bytes);              // 分配内存
    if (NULL == line_buf)
    {
        fprintf(stderr, "malloc error\n");
        close(fd_BMP);
        return -1;
    }
    if (line_length > line_bytes)   // 从设备获取到的【行数据量】 > 计算得到的【行数据量】
        min_bytes = line_bytes;     // 最小行数据量取二者中小的那个
    else
        min_bytes = line_length;

    
    /**** 读取图像数据显示到 LCD ****/
    /*******************************************
     * 为了软件处理上方便，这个示例代码便不去做兼容性设计了
     * 如果你想做兼容, 可能需要判断传入的 BMP 图像是 565 还是 888
     * 如何判断呢？文档里边说的很清楚了
     * 我们默认传入的 bmp 图像是 RGB565 格式
     *******************************************/
    if (0 < info_h.height)//倒向位图
    {
        if (info_h.height > height) // 【图片】的高度 > 【屏幕】的高度
        {
            min_h = height;         // 最小高度 赋值为 二者中小的那个
            lseek(fd_BMP, (info_h.height - height) * line_bytes, SEEK_CUR); // （【图片】高度 - 【屏幕】高度） * 每行字节数
            /* 也就是把图片高于屏幕，多出来的那部分剪掉，不显示在屏幕上。 */
            screen_base += width * (min_h - 1); //定位到屏幕左下角位置
        }
        else                        // 图片的高度 < 屏幕的高度
        {
            min_h = info_h.height;  // 最小高度 赋值为 二者中小的那个
            screen_base += width * (min_h - 1); //定位到屏幕左下角位置
        }
        for (j = min_h; j > 0; screen_base -= width, j--)
        {
            read(fd_BMP, line_buf, line_bytes); //读取出【一行】图像数据，放到 line_buf 中。
            memcpy(screen_base, line_buf, min_bytes);//刷入 LCD 显存
        }
    }
    else//正向位图
    { 
        int temp = 0 - info_h.height; //负数转成正数
        if (temp > height)  // 【图象】高度 > 【屏幕】高度的情况
            min_h = height;
            lseek(fd_BMP, (temp - height) * line_bytes, SEEK_CUR); // （【图片】高度 - 【屏幕】高度） * 每行字节数
            /* 也就是把图片高于屏幕，多出来的那部分剪掉，不显示在屏幕上。 */
        else
            min_h = temp;
        for (j = 0; j < min_h; j++, screen_base += width)
        {
            read(fd_BMP, line_buf, line_bytes);
            memcpy(screen_base, line_buf, min_bytes);
        }
    }

    /* 关闭文件、函数返回 */
    close(fd_BMP);
    free(line_buf);
    return 0;
}


int main(int argc, char *argv[])
{
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
    unsigned int screen_size;
    int fd_LCD;

    /* 传参校验 */
    if (2 != argc)
    {
        fprintf(stderr, "usage: %s <bmp_file>\n", argv[0]);
        exit(-1);
    }

    /* 打开 framebuffer 设备 */
    if (0 > (fd_LCD = open("/dev/fb0", O_RDWR)))
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    /* 获取参数信息 */
    ioctl(fd_LCD, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd_LCD, FBIOGET_FSCREENINFO, &fb_fix);
    screen_size = fb_fix.line_length * fb_var.yres;
    line_length = fb_fix.line_length;
    width = fb_var.xres;    // 设备文件中提取出来的【屏幕】的x分辨率，一行有多少个像素点
    height = fb_var.yres;   // 设备文件中提取出来的【屏幕】的y分辨率，一列有多少个像素点

    /* 将显示缓冲区映射到进程地址空间 */
    screen_base = mmap(NULL, screen_size, PROT_WRITE, MAP_SHARED, fd_LCD, 0);
    if (MAP_FAILED == (void *)screen_base)
    {
        perror("mmap error");
        close(fd_LCD);
        exit(EXIT_FAILURE);
    }

    /* 显示 BMP 图片 */
    memset(screen_base, 0xFF, screen_size);
    show_bmp_image(argv[1]);        // 调用上面自定义的函数

    /* 退出 */
    munmap(screen_base, screen_size); //取消映射
    close(fd_LCD); //关闭文件
    exit(EXIT_SUCCESS); //退出进程
}