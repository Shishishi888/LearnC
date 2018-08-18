#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct
{
    int *base;     //Õ»µ×Ö¸Õë
    int *top;      //Õ»¶¥Ö¸Õë
    int stacksize; //Õ»¿ÉÓÃµÄ×î´óÈÝÁ¿
}SqStack;

/*Ë³ÐòÕ»µÄ³õÊ¼»¯*/
int InitStack(SqStack *S)
{
    S->base=(int *)malloc(sizeof(int)*MAX);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAX;
    return OK;
}

/*Ë³ÐòÕ»µÄÈëÕ»*/
int Push(SqStack *S, int e)
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *((S->top)++)=e;
    return OK;
}

/*Ë³ÐòÕ»µÄ³öÕ»*/
int Pop(SqStack *S, int *e)
{
    if(S->top=S->base)
        return ERROR;
    e=--(S->top);
    return OK;
}

/*È¡Õ»¶¥ÔªËØ*/
int GetTop(SqStack *S)
{
    if(S->top!=S->base)
        return *(S->top-1);
}

/*ÅÐ¶ÏË³ÐòÕ»ÊÇ·ñÎª¿Õ*/
bool StackEmpty(SqStack *S)
{
    if(S->top==S->base)
        return true;
    else
        return false;
}

/*ÇóË³ÐòÕ»µÄ³¤¶È*/
int StackLength(SqStack *S)
{
    return S->top-S->base;
}

/*Çå¿ÕË³ÐòÕ»*/
int ClearStack(SqStack *S)
{
    if(S->base)
        S->top=S->base;
    return OK;
}

/*Ïú»ÙË³ÐòÕ»*/
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









