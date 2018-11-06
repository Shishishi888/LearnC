#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
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
int GetElem(LinkList L, int i, ElemType *e)
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
    *e=p->data;
    return OK;
}

/*单链表的按值查找*/
LNode *LocateElem(LinkList L, ElemType e)
{
    LNode *p=L->next;
    while(p&&p->data!=e)
        p=p->next;
    return p;//查找成功返回值为e的结点地址p，查找失败p为NULL
}

/*单链表的插入*/
int ListInsert(LinkList *L, int i, ElemType e)
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

/*合并单链表*/
void MergeList(LinkList *LA, LinkList LB)
{//将所有在线性表LB中但不在LA中的数据元素插入到LA中
    int m=GetLength_L(*LA);
    int n=GetLength_L(LB);

    for(int i=0; i<=n; i++){
        ElemType e;
        GetElem(LB, i, &e);
        if(!LocateElem(*LA, e))
            ListInsert(LA, ++m, e);
    }
}

/*合并链式有序表*/
void MergeList_L(LinkList *LA, LinkList *LB, LinkList *LC)
{//已知单链表LA和LB的元素按值非递减排列
 //归并LA和LB得到新的单链表LC，LC的元素也按值非递减排列

    LNode *pa=(*LA)->next;//pa的初值指向LA的首元结点
    LNode *pb=(*LB)->next;//pb的初值指向LB的首元结点

    LC=LA;//用LA的头结点作为LC的头结点
    LNode *pc=(*LA)->next;//pc的初值指向LC的头结点

    while(pa&&pb)
    {
        if(pa->data<=pb->data)//如果当前pa的data小于或等于pb的data
        {
            pc->next=pa;
            pc=pa;//pc指向当前pa和pb中较小的结点，即pa
            pa=pa->next;//pa指向La链表中的下一个结点
        }

        else//如果当前pa的data大于pb的data
        {
            pc->next=pb;
            pc=pb;//pc指向当前pa和pb中较小的结点，即pb
            pb=pb->next;//pb指向Lb链表中的下一个结点
        }
    }

    pc->next=pa?pa:pb;//将非空链表的剩余结点直接连接到Lc链表的最后
    free(LB);
}


