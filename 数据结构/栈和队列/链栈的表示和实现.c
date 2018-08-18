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

/*链栈的初始化*/
int InitStack(LinkStack *S)
{
    *S=NULL;
    return OK;
}

/*链栈的入栈*/
int Push(LinkStack *S, int e)
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=e;
    p->next=*S;
    *S=p;
    return OK;
}

/*链栈的出栈*/
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

/*取栈顶元素*/
int GetTop(LinkStack S)
{
    if(S!=NULL)
        return S->data;
}

/*判断链栈是否为空*/
bool StackEmpty(LinkStack S)
{
    if(S==NULL)
        return true;
    else
        return false;
}

