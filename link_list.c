#include "myhead.h"

//定义双向循环链表
struct single_list
{
    char bmp_path[100];//数据域，存放的数据内容
    struct single_list *prev;//指针域，存放上一个数据的地址
    struct single_list *next;//指针域，存放下一个数据的地址
};
//初始化(头节点)
struct single_list *slist_init()
{
    //定义结构体指针，申请堆空间
    struct single_list *list=malloc(sizeof(struct single_list));
    //指针指向哪里
    list->next= list; 
    list->prev= list;
    return list;
}
//尾插数据
int slist_add_tail(char *newpath,struct single_list *list)
{
    //定义结构体指针，申请堆空间
    struct single_list *newnode=malloc(sizeof(struct single_list));
    strcpy(newnode->bmp_path,newpath);
    //指针指向哪里
    struct single_list *p=list;
    while (p->next!=list)
        p=p->next;
    p->next=newnode;
    newnode->prev=p;

    newnode->next=list;
    list->prev=newnode;
    return 0;
}
//插入数据
int slist_add(char *oldpath,char *newpath,struct single_list *list)
{
    struct single_list *p=list->next;
    int flgs=0;//标志位

    while (p!=list)
    {
        if(strcmp(p->bmp_path,oldpath)==0)
        {
             //定义结构体指针，申请堆空间
            struct single_list *newnode=malloc(sizeof(struct single_list));
             strcpy(newnode->bmp_path,newpath);
            newnode->next= NULL; 
            newnode->prev= NULL;
            //指针指向哪里
            newnode->next=p->next;
            newnode->next->prev=newnode;
            p->next=newnode;
            newnode->prev=p;
            //p向下遍历
            p=newnode->next;
            flgs=1;
        }
        else
            p=p->next;
    }
    if(flgs==0)
        printf("未插入%s数据\n",newpath);
    return 0;
}

//删除数据
int list_delete(char *delpath, struct single_list *list)
{
    int flgs = 0;
    struct single_list *p=list->next;
    while (p!=list)
    {
        if(strcmp(p->bmp_path,delpath)==0)
        {
            struct single_list *temp = p;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p = p->next;
            temp->next=NULL;
            temp->prev=NULL;
            free(temp);
            flgs =1;//已经删除数据
        }
        else
            p=p->next;
    }
    if(flgs==0)
        printf("未删除%s数据\n",delpath);
    return 0;
    
}
//打印数据
int slist_show(struct single_list *list)
{
    //定义一个结构体指向指向链表结构体
    struct single_list *p=list->next;
    if(p==list)
    {
        printf("这个链表为空！\n");
        return -1;
    }
    while(p!=list)
    {
        printf("目前遍历的数据是：%s\n",p->bmp_path);
        p=p->next;//循环结束时p指向最后一个节点打的位置 
    }
}

/* int main()
{
    struct single_list *mylist=slist_init();
    //尾插数据
    slist_add_tail("./BMP/1.bmp",mylist);
    //插入数据
    slist_add("./BMP/1.bmp","./BMP/2.bmp",mylist);
    slist_add("./BMP/2.bmp","./BMP/3.bmp",mylist);
    //删除数据
    list_delete("./BMP/3.bmp",mylist);
    //打印数据
    slist_show(mylist);
    return 0;
} */