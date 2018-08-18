#include <stdio.h>
#include <stdlib.h>
#define MAX 20                                          //˳����Ա���������
#define OK 1
#define ERROR 0

typedef struct
{
    int *elem;
    int length;                                         //˳���ĳ�Ա����
    int list_size;                                      //˳���ռ���ڴ�ռ��С
}SqList;

/*˳���ĳ�ʼ��*/
int InitList(SqList *L)
{
    L->elem=(int *)malloc(MAX*sizeof(int));             //Ϊ˳������һ���ڴ�ռ䣬˳���ĳ�Ա����Ϊ����
    if(!L->elem)
        exit(0);
    L->length=0;
    return OK;
}

/*˳����ȡֵ*/
int GetElem(SqList *L, int i, int *e)                   //�����������������OK��ʾȡֵ�ɹ�����ָ��eָ��ȡ����ֵ
{
    if(i<1||i>L->length)
        return ERROR;
    e=&(L->elem[i-1]);
    return OK;
}

/*˳���Ĳ���*/
int LocateElem(SqList *L, int e)
{
    for(int i=0;i<L->length;i++)
    {
        if(L->elem[i]==e)
            return i+1;
    }
    return 0;
}

/*˳���Ĳ���*/
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

/*˳����ɾ��*/
int ListDelete(SqList *L, int i)
{
    if((i<1)||(i>L->length))
        return ERROR;
    for(int j=i;j<L->length-1;j++)
        L->elem[j-1]=L->elem[j];
    --L->length;
    return OK;
}

/*����˳���*/
void DestroyList(SqList *L)
{
    if(L->elem)
        free(L->elem);
}

/*���˳���*/
void ClearList(SqList *L)
{
    L->length=0;
}

/*��˳���ĳ���*/
int GetLength(SqList *L)
{
    return L->length;
}

/*�ж�˳����Ƿ�Ϊ��*/
int IsEmpty(SqList *L)
{
    if(L->length==0)
        return 1;
    else
        return 0;
}
