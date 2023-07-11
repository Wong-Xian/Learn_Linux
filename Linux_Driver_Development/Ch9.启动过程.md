# 启动过程详解

## 4种启动模式 BOOT_MODE[1:0]

1. 00 从fuse启动：第一种修改 eFUSE 的方式只能修改一次，后面就不能再修改了，所以我们不使用。
2. 01 串行下载：串行下载的意思就是可以通过 USB 或者 UART 将代码下载到板子上的外置存储设备中，我们可以使用 OTG1 这个 USB 口向开发板上的 SD/EMMC、NAND 等存储设备下载代码。
3. 10 内部BOOT模式：在此模式下，芯片会执行内部的 boot ROM 代码，这段 boot ROM 代码会进行硬件初始化(一部分外设)，然后从 boot 设备(就是存放代码的设备、比如 SD/EMMC、NAND)中将代码拷贝出来复制到指定的 RAM 中，一般是 DDR。
4. 11 保留

## BOOT ROM 初始化内容

1. 初始化时钟
2. 内部 boot ROM 为加速，打开 MMU 和 Cache
3. 中断向量偏移被舍之道 boot ROM 起始位置

## 启动设备

可选启动设备
1. 接到 EIM 接口 CS0 上的 NOR Flash 或 NAND Flash
2. 接到 GPMI 接口上的 MLC/SLC NAND Flash
3. 接到 Quad SPI Flash
4. 接到 USDHC 接口上的 SD/MMC/eSD/SDXC/eMMC 等设备。
5. 接到 SPI 接口的 EEPROM。

可通过 eFUSE 和 GPIO 配置启动设备

由 BOOT_FCG1 BOOT_FCG2 BOOT_FCG4 三个寄存器（每个8位）共24位控制，其中有用的只有 BOOT_FCG2[3] BOOT_FCG1[3] BOOT_FCG1[4] BOOT_FCG1[5] BOOT_FCG1[6] BOOT_FCG1[7]

镜像烧写过程

I.MX6U 需求的最终可烧写文件包括以下几部分： Image Vector Table（地址信息） Boot Data （启动数据） Device Configuration Data（设备配置信息） bin可执行文件