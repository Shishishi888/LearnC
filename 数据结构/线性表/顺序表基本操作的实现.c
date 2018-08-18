#include <stdio.h>
#include <stdlib.h>
#define MAX 20                                          //顺序表成员的最大数量
#define OK 1
#define ERROR 0

typedef struct
{
    int *elem;
    int length;                                         //顺序表的成员个数
    int list_size;                                      //顺序表占的内存空间大小
}SqList;

/*顺序表的初始化*/
int InitList(SqList *L)
{
    L->elem=(int *)malloc(MAX*sizeof(int));             //为顺序表分配一个内存空间，顺序表的成员类型为整型
    if(!L->elem)
        exit(0);
    L->length=0;
    return OK;
}

/*顺序表的取值*/
int GetElem(SqList *L, int i, int *e)                   //完成两个工作：返回OK表示取值成功；将指针e指向取到的值
{
    if(i<1||i>L->length)
        return ERROR;
    e=&(L->elem[i-1]);
    return OK;
}

/*顺序表的查找*/
int LocateElem(SqList *L, int e)
{
    for(int i=0;i<L->length;i++)
    {
        if(L->elem[i]==e)
            return i+1;
    }
    return 0;
}

/*顺序表的插入*/
int ListInsert(SqList *L, int i, int e)
{
    if((i<1)||(i>L->length+1))
        return ERROR;
    if(L->length=MAX)
        return ERROR;
    for(int j=L->length-1;j>=i-1;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i-1]=e;
    ++L->length;
    return OK;
}

/*顺序表的删除*/
int ListDelete(SqList *L, int i)
{
    if((i<1)||(i>L->length))
        return ERROR;
    for(int j=i;j<L->length-1;j++)
        L->elem[j-1]=L->elem[j];
    --L->length;
    return OK;
}

/*销毁顺序表*/
void DestroyList(SqList *L)
{
    if(L->elem)
        free(L->elem);
}

/*清空顺序表*/
void ClearList(SqList *L)
{
    L->length=0;
}

/*求顺序表的长度*/
int GetLength(SqList *L)
{
    return L->length;
}

/*判断顺序表是否为空*/
int IsEmpty(SqList *L)
{
    if(L->length==0)
        return 1;
    else
        return 0;
}
