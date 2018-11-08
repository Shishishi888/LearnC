#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                                          //顺序表成员的最大数量
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct
{
    ElemType *elem;
    int length;                                         //顺序表的成员个数
    int list_size;                                      //顺序表占的内存空间大小
}SqList;

/*顺序表的初始化*/
int InitList(SqList *L)
{
    L->elem=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));             //为顺序表分配一个内存空间，顺序表的成员类型为整型
    if(!L->elem)
        exit(0);
    L->length=0;
    L->list_size=MAXSIZE;
    return OK;
}

/*创建顺序表*/
void CreateList(SqList *L)
{
    if(!L->elem)
        exit(0);
    for(int i=0; i<L->list_size; i++)
    {
        int e;
        scanf("%d", &e);

        if(e==-1)
            break;

        L->elem[i]=e;
        L->length++;
    }
}

/*顺序表的遍历*/
void ListTraverse(SqList L)
{
    if(!L.elem) exit(0);

    for(int i=0; i<L.length; i++)
        printf("%3d", L.elem[i]);

    /*
    for(int i=0; i<L.length; i++)
    {
        printf("%3d", *L.elem);
        L.elem++;
    }
    */
}

/*顺序表的取值*/
int GetElem(SqList L, int i, ElemType *e)                   //完成两个工作：返回OK表示取值成功；将指针e指向取到的值
{
    if(i<1||i>L.length)
        return ERROR;
    *e=L.elem[i-1];
    return OK;
}

/*顺序表的查找*/
int LocateElem(SqList L, ElemType e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i]==e)
            return i+1;
    }
    return 0;
}

/*顺序表的插入*/
int ListInsert(SqList *L, int i, ElemType e)
{
    if((i<1)||(i>L->length+1))
        return ERROR;
    if(L->length=MAXSIZE)
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
int GetLength(SqList L)
{
    return L.length;
}

/*判断顺序表是否为空*/
int IsEmpty(SqList L)
{
    if(L.length==0)
        return 1;
    else
        return 0;
}

/*合并顺序表*/
void MergeList(SqList *LA, SqList LB)
{//将所有在线性表LB中但不在LA中的数据元素插入到LA中
    int m=GetLength(*LA);
    int n=GetLength(LB);

    for(int i=0; i<n; i++)
    {
        ElemType e;
        GetElem(LB, i, &e);
        if(!LocateElem(*LA, e))
            ListInsert(LA, ++m, e);
    }
}

/*合并顺序有序表*/
void MergeList_Sq(SqList LA, SqList LB, SqList *LC)
{//已知顺序有序表LA和LB的元素按值非递减排列
 //归并LA和LB得到新的的顺序有序表LC，LC的元素也按值非递减排列

    LC->length=LA.length+LB.length;//新表长度为代合并两表长度之和
    LC->elem=(ElemType *)malloc(sizeof(ElemType)*LC->length);//为合并后的新表分配一个数组空间

    ElemType *pa=LA.elem;//指针pa指向LA的第一个元素
    ElemType *pb=LA.elem;//指针pb指向LB的第一个元素
    ElemType *pa_last=LA.elem+LA.length-1;//指针pa_last指向LA的最后一个元素
    ElemType *pb_last=LB.elem+LB.length-1;//指针pb_last指向LB的最后一个元素

    ElemType *pc=LA.elem;//指针pc指向新表的第一个元素

    while(pa<=pa_last&&pb<=pb_last)
    {
        if(*pa<=*pb)    *pc++=*pa++;//依次摘取两表中较小的结点插入到LC的最后
        else            *pc++=*pb++;
    }

    while(pa<=pa_last)  *pc++=*pa++;//LB已到达末尾，依次将LA的剩余元素插入到LC的最后
    while(pb<pb_last)   *pc++=*pb++;//LA已到达末尾，依次将LB的剩余元素插入到LC的最后
}

