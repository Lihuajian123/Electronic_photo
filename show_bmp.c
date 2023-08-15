//显示bmp图片
#include "myhead.h"
#define BMP_Pixel_range    800*480*3
#define Board_Pixel_range  800*480*4
int show_bmp(char *pathname)
{
    int bmp=open(pathname,O_RDWR);
    if(bmp==-1)
    {
        perror("图片打开失败！\n");
        return -1;
    }
    
    //读取图片的头信息
    char head[54]={0};
    read(bmp,head,54);
    //读取图片像素点
    char rgb[BMP_Pixel_range];
    read(bmp,rgb,BMP_Pixel_range);

    //关闭图片
    close(bmp);
    
    //打开液晶屏的驱动
    int fd;
    fd=open("/dev/fb0",O_RDWR);
    if(fd==-1)
    {
        perror("液晶屏驱动打开失败！\n");
        return -1;
    }
    //图片适配液晶屏
    char argb[Board_Pixel_range];
    for(int i=0;i<(Board_Pixel_range)/4;i++)
    {
        argb[0+i*4]=rgb[0+i*3];       // b
        argb[1+i*4]=rgb[1+i*3];       // g
        argb[2+i*4]=rgb[2+i*3];       // r
        argb[3+i*4]=0;                // a
    }
    //对LCD液晶屏进行映射
    int(*lcd)[800]= mmap(NULL,Board_Pixel_range, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int(*color)[800] = (void *)argb;
   /*  //把像素数据放入映射空间
    for (int i = 0; i < Board_Pixel_range; i++)
    {
        lcd[i] = argb[i];
    } */
    // 把像素数据放入映射空间(实现图片倒转)
    for (int y = 0; y < 480; y++)
        for (int x = 0; x < 800; x++)
        {
            lcd[y][x] = color[479 - y][x];
        }

    close(fd);
    //解除映射
    munmap(lcd,Board_Pixel_range);
    return 0;
}