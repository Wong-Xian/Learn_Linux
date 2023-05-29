# FrameBuffer 应用编程

## 19.1 什么是 FrameBuffer

帧缓冲（framebuffer）是 Linux 系统中的一种显示驱动接口

## 19.2 LCD的基础知识

## 19.3 LCD应用编程介绍

### 19.3.1 使用ioctl获取屏幕参数信息

### 19.3.2 使用mmap()将显示缓冲区映射到用户空间

## 19.4 LCD应用编程练习之LCD基本操作

## 19.5 LCD应用编程练习之BMP图片显示

### 19.5.1 BMP图象介绍

1. BMP文件头(BMP file header)（14字节）
   1. bfType：BMP文件类型（2字节）
      1. BM-Windows
      2. BA-Bitmap Array
      3. CI-Color Icon
      4. CP-Color Pointer
      5. IC-Icon
      6. PT-Pointer
   2. bfSize：文件大小，单位是字节（4字节）
   3. bfReserved1：保留（2字节）
   4. bfReserved2：保留（2字节）
   5. bfOffBits：从文件起始位置到图像数据之间的字节偏移量（4字节）
2. 位图信息头(bitmap information header)
   1. biSize：位图信息头大小（4字节）
   2. biWidth：图象宽度，像素为单位（4字节）
   3. biHeight：图象高度，像素为单位（4字节）
   4. biPlanes：色彩平面数（2字节）
   5. biBitCount：像素深度，一个像素点需要多少位数据来描述（2字节）
   6. biCompression：图象数据压缩类型（4字节）
      1. 0-RGB方式
      2. 1-8bpp的RLE方式，用于8bit位图
      3. 2-4bpp的RLE方式，用于4bit位图
      4. 3-Bit-field方式
      5. 4-用于打印机
      6. 5-用于打印机
   7. biSizeImage：说明图象的大小（4字节）
   8. biXPelsPerMeter：水平分辨率（像素/米），有符号整数，单位字节（4字节）
   9. biYPelsPerMeter：垂直分辨率（像素/米），有符号整数，单位字节（4字节）
   10. biClrUsed：位图实际使用的彩色表中的颜色索引数（4字节）
   11. biClrImportant：位图实际使用的彩色表中的颜色索引数（4字节）
3. 调色板(color palette)
4. 位图数据(bitmap data)