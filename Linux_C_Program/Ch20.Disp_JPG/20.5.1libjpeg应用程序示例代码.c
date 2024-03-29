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
#include <jpeglib.h>


typedef struct bgr888_color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} __attribute__ ((packed)) bgr888_t;

static int width; //LCD X 分辨率
static int height; //LCD Y 分辨率
static unsigned short *screen_base = NULL; //映射后的显存基地址
static unsigned long line_length; //LCD 一行的长度（字节为单位）
static unsigned int bpp; //像素深度 bpp

static int show_jpeg_image(const char *path)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *jpeg_file = NULL;
    bgr888_t *jpeg_line_buf = NULL; //行缓冲区:用于存储从 jpeg 文件中解压出来的一行图像数据
    unsigned short *fb_line_buf = NULL; //行缓冲区:用于存储写入到 LCD 显存的一行数据
    unsigned int min_h, min_w;
    unsigned int valid_bytes;
    int i;

    //绑定默认错误处理函数
    cinfo.err = jpeg_std_error(&jerr);

    //打开.jpeg/.jpg 图像文件
    jpeg_file = fopen(path, "r"); //只读方式打开
    if (NULL == jpeg_file)
    {
        perror("fopen error");
        return -1;
    }

    //创建 JPEG 解码对象
    jpeg_create_decompress(&cinfo);

    //指定图像文件
    jpeg_stdio_src(&cinfo, jpeg_file);

    //读取图像信息
    jpeg_read_header(&cinfo, TRUE);
    printf("jpeg 图像大小: %d*%d\n", cinfo.image_width, cinfo.image_height);

    //设置解码参数
    cinfo.out_color_space = JCS_RGB;//默认就是 JCS_RGB
    //cinfo.scale_num = 1;
    //cinfo.scale_denom = 2;

    //开始解码图像
    jpeg_start_decompress(&cinfo);

    //为缓冲区分配内存空间
    jpeg_line_buf = malloc(cinfo.output_components * cinfo.output_width);
    fb_line_buf = malloc(line_length);

    //判断图像和 LCD 屏哪个的分辨率更低
    if (cinfo.output_width > width)
        min_w = width;
    else
        min_w = cinfo.output_width;
    
    if (cinfo.output_height > height)
        min_h = height;
    else
        min_h = cinfo.output_height;

    
    //读取数据
    valid_bytes = min_w * bpp / 8;//一行的有效字节数 表示真正写入到 LCD 显存的一行数据的大小
    while (cinfo.output_scanline < min_h)
    {
        jpeg_read_scanlines(&cinfo, (unsigned char **)&jpeg_line_buf, 1);//每次读取一行数据
        //将读取到的 BGR888 数据转为 RGB565
        for (i = 0; i < min_w; i++)
            fb_line_buf[i] = ((jpeg_line_buf[i].red & 0xF8) << 8) | ((jpeg_line_buf[i].green & 0xFC) << 3) | ((jpeg_line_buf[i].blue & 0xF8) >> 3);
                                // F8 -> 1111 1000  Low_Addr               FC -> 1111 1100   Mid_Addr            F8 -> 1111 1000   High_Addr
        memcpy(screen_base, fb_line_buf, valid_bytes);
        screen_base += width;//+width 定位到 LCD 下一行显存地址的起点
    }

    //解码完成
    jpeg_finish_decompress(&cinfo);
    
    //销毁 JPEG 解码对象、释放资源
    jpeg_destroy_decompress(&cinfo);

    //关闭文件、释放内存
    fclose(jpeg_file);
    free(fb_line_buf);
    free(jpeg_line_buf);
    return 0;
}


int main(int argc, char *argv[])
{
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
    unsigned int screen_size;
    int fd;

    /* 传参校验 */
    if (2 != argc)
    {
        fprintf(stderr, "usage: %s <jpeg_file>\n", argv[0]);
        exit(-1);
    }

    /* 打开 framebuffer 设备 */
    if (0 > (fd = open("/dev/fb0", O_RDWR)))
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    /* 获取参数信息 */
    ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix);
    line_length = fb_fix.line_length;
    bpp = fb_var.bits_per_pixel;
    screen_size = line_length * fb_var.yres;
    width = fb_var.xres;
    height = fb_var.yres;

    /* 将显示缓冲区映射到进程地址空间 */
    screen_base = mmap(NULL, screen_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == (void *)screen_base)
    {
        perror("mmap error");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* 显示 BMP 图片 */
    memset(screen_base, 0xFF, screen_size);
    show_jpeg_image(argv[1]);

    /* 退出 */
    munmap(screen_base, screen_size); //取消映射
    close(fd); //关闭文件
    exit(EXIT_SUCCESS); //退出进程
}