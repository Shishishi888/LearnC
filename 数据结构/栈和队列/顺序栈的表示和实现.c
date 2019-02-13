#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int SElemType;

typedef struct
{
    SElemType *base;     //ջ��ָ��
    SElemType *top;      //ջ��ָ��
    int stacksize; 		 //ջ���õ��������
}SqStack;

/*˳��ջ�ĳ�ʼ��*/
int InitStack(SqStack *S)
{
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

/*˳��ջ����ջ*/
int Push(SqStack *S, SElemType e)
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

/*˳��ջ�ĳ�ջ*/
int Pop(SqStack *S, SElemType *e)
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

/*ȡջ��Ԫ��*/
int GetTop(SqStack S)
{
    if(S.top!=S.base)
        return *(S.top-1);
}

/*�ж�˳��ջ�Ƿ�Ϊ��*/
bool StackEmpty(SqStack S)
{
    if(S.top==S.base)
        return true;
    else
        return false;
}

/*��˳��ջ�ĳ���*/
int StackLength(SqStack S)
{
    return S.top-S.base;
}

/*���˳��ջ*/
int ClearStack(SqStack *S)
{
    if(S->base)
        S->top=S->base;
    return OK;
}

/*����˳��ջ*/
int DestroyStack(SqStack *S)
{
    if(S->base)
    {
        free(S->base);
        S->stacksize=0;
        S->base=S->top=NULL;
    }
    return OK;
}

void main(){}
