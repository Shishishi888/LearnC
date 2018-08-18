#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *LinkList;//LinkList为指向结构体LNode的指针类型
/*为了提高程序的可读性，在此对同一结构体指针类型起了两个名称，LinkList与LNode*，两者本质上是等价的。通常习惯上用LinkList
定义单链表，强调定义的是某个单链表的头指针；用LNode*定义指向单链表中任意结点的指针变量*/

/*单链表的初始化*/
int InitList(LinkList *L)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

/*单链表的取值*/
int GetElem(LinkList L, int i, int *e)
{
    LNode *p=L->next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    e=&(p->data);
    return OK;
}

/*单链表的按值查找*/
LNode *LocateElem(LinkList L, int e)
{
    LNode *p=L->next;
    while(p&&p->data!=e)
        p=p->next;
    return p;//查找成功返回值为e的结点地址p，查找失败p为NULL
}

/*单链表的插入*/
int ListInsert(LinkList *L, int i, int e)
{
    LNode *p=*L;
    int j=0;
    while(p&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i-1)
        return ERROR;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

/*单链表的删除*/
int ListDelete(LinkList *L, int i)
{
    LNode *p=*L;
    int j=0;
    while((p->next)&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||(j>i-1))
        return ERROR;
    LNode *q=p->next;
    p->next=q->next;
    free(p);
    return OK;
}


/*前插法创建单链表*/
void CreateList_H(LinkList *L, int n)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    int i;
    for(i=0;i<n;++i)
    {
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=(*L)->next;
        (*L)->next=p;
    }
}

/*后插法创建单链表*/
void CreateList_R(LinkList *L, int n)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    LNode *r=*L;
    int i;
    for(i=0;i<n;++i)
    {
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

/*销毁单链表*/
int DestroyList_L(LinkList *L)
{
    LinkList p;
    while(*L)
    {
        p=*L;
        *L=(*L)->next;
        free(p);
    }
    return OK;
}

/*清空单链表*/
int ClearList(LinkList *L)
{
    LinkList p, q;
    p=(*L)->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;
    return OK;
}

/*求单链表的长度*/
int GetLength_L(LinkList L)
{
    LinkList p=L->next;
    int i=0;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

/*判断单链表是否为空*/
int IsEmpty_L(LinkList L)
{
    if(L->next)
        return 0;
    else
        return 1;
}

