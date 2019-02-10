#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

/*循环队列的初始化*/
int InitQueue(SqQueue *Q)
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!(Q->base))
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

/*求循环队列的长度*/
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAX)%MAX;
}

/*循环队列的入队*/
int EnQueue(SqQueue *Q, int e)
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

/*循环队列的出队*/
int DeQueue(SqQueue *Q, int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

/*取循环列表的队头元素*/
int GetHead(SqQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.base[Q.front];
}
