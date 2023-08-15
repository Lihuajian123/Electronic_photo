#ifndef _LCD_H
#define _LCD_H

//显示24位bmp图片的函数
int show_bmp(char *pathname);
//触摸屏坐标获取的函数声明
int getcrood(int *gx, int *gy);

#endif