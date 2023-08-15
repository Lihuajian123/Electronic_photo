#include "myhead.h"
#include "LCD.h"
#include "opendir.h"
#include "link_list.h"
#define FILE_TYPE ".bmp"
int main(int argc, char **argv)
{
    //定义一个双向循环链表保存图片路径
    struct single_list *bmp_path_list=slist_init();
    int ret;
    //打开目录读取文件,保存在链表中
    ret=openDIR(argv[1],".bmp",bmp_path_list);
    if (ret == -1)
    {
        printf("打开目录失败\n");
        return 1;
    }

    //获取坐标
    int flgs;
    int x=0,y=0;
    int i=1;
    struct single_list *p=bmp_path_list->next;
    //显示第一张图片
    show_bmp(p->bmp_path);//显示第一张图片(主界面)
    while (1)
    {
        flgs=getcrood(&x,&y);
        if(x<512)//左滑动
        {
            p=p->prev;
            if(p==bmp_path_list)
            {
                p=p->prev;
            }
            show_bmp(p->bmp_path);
        }
        if(x>=512 && x<=1023)//右滑动
        {
            p=p->next;
            if(p==bmp_path_list)
            {
                p=p->next->next;
            }
            show_bmp(p->bmp_path);
        } 
    }
    //销毁链表
    while (p->next!=bmp_path_list)
        p=p->next;
    while (p!=bmp_path_list)
    {
        p=p->prev;
        free(p->next);
    }
    return 0;
}

	