#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct
{
    int *base;     //ջ��ָ��
    int *top;      //ջ��ָ��
    int stacksize; //ջ���õ��������
}SqStack;

/*˳��ջ�ĳ�ʼ��*/
int InitStack(SqStack *S)
{
    S->base=(int *)malloc(sizeof(int)*MAX);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAX;
    return OK;
}

/*˳��ջ����ջ*/
int Push(SqStack *S, int e)
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *((S->top)++)=e;
    return OK;
}

/*˳��ջ�ĳ�ջ*/
int Pop(SqStack *S, int *e)
{
    if(S->top=S->base)
        return ERROR;
    e=--(S->top);
    return OK;
}

/*ȡջ��Ԫ��*/
int GetTop(SqStack *S)
{
    if(S->top!=S->base)
        return *(S->top-1);
}

/*�ж�˳��ջ�Ƿ�Ϊ��*/
bool StackEmpty(SqStack *S)
{
    if(S->top==S->base)
        return true;
    else
        return false;
}

/*��˳��ջ�ĳ���*/
int StackLength(SqStack *S)
{
    return S->top-S->base;
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









