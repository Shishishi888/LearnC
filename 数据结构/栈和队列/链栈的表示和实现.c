#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OK 1
#define ERROR 0

typedef struct StackNode
{
    int data;
    struct StackNode *next;
}StackNode, *LinkStack;

/*��ջ�ĳ�ʼ��*/
int InitStack(LinkStack *S)
{
    *S=NULL;
    return OK;
}

/*��ջ����ջ*/
int Push(LinkStack *S, int e)
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=e;
    p->next=*S;
    *S=p;
    return OK;
}

/*��ջ�ĳ�ջ*/
int Pop(LinkStack *S, int *e)
{
    if(*S==NULL)
        return ERROR;
    e=&((*S)->data);
    StackNode *p=*S;
    *S=(*S)->next;
    free(p);
    return OK;
}

/*ȡջ��Ԫ��*/
int GetTop(LinkStack S)
{
    if(S!=NULL)
        return S->data;
}

/*�ж���ջ�Ƿ�Ϊ��*/
bool StackEmpty(LinkStack S)
{
    if(S==NULL)
        return true;
    else
        return false;
}

