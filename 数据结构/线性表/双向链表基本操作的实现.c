#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef struct DuLNode
{
    int data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

/*双向链表的初始化*/
int InitList_DuL(DuLinkList *L)
{
    *L=(DuLNode *)malloc(sizeof(DuLNode));
    (*L)->prior=NULL;
    (*L)->next=NULL;
    return OK;
}

/*双向链表的取值*/
DuLNode *GetElem_DuL(DuLinkList L, int i)
{
    DuLNode *p=L->next;
    int j=0;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    return p;
}

/*双向链表的按值查找*/
DuLNode *LocateElem_DuL(DuLinkList L, int e)
{
    DuLNode *p=L->next;
    while(p&&p->data!=e)
        p=p->next;
    return p;
}

/*双向链表的插入*/
int ListInsert_DuL(DuLinkList *L, int i, int e)
{
    DuLNode *p;
    if(!(p=GetElem_DuL(*L, i)))
       return ERROR;
    DuLNode *s=(DuLNode *)malloc(sizeof(DuLNode));
    s->data=e;
    s->prior=p->prior;
    p->prior->next=s;
    s->next=p;
    p->prior=s;
    return OK;
}

/*双向链表的删除*/
int ListDelete_DuL(DuLinkList *L, int i)
{
    DuLNode *p;
    if(!(p=GetElem_DuL(*L, i)))
        return ERROR;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    free(p);
    return OK;
}
