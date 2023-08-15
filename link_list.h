#ifndef _LINK_LIST_H
#define _LINK_LIST_H

//定义双向循环链表
struct single_list
{
    char bmp_path[100];//数据域，存放的数据内容
    struct single_list *prev;//指针域，存放上一个数据的地址
    struct single_list *next;//指针域，存放下一个数据的地址
};
//链表功能函数的声明
struct single_list *slist_init();   //初始化链表
//尾插数据
int slist_add_tail(char *newpath,struct single_list *list);
//插入数据
int slist_add(char *oldpath,char *newpath,struct single_list *list);
//删除数据
int list_delete(char *delpath, struct single_list *list);
//打印数据
int slist_show(struct single_list *list);
#endif