#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OK 1
#define ERROR 0

typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

/*链队的初始化*/
int InitQueue(LinkQueue *Q)
{
    Q->front=Q->rear=(QNode *)malloc(sizeof(QNode));
    Q->front->next=NULL;
    return OK;
}

/*链队的入队*/
int EnQueue(LinkQueue *Q, int e)
{
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
    return OK;
}

/*链队的出队*/
int DeQueue(LinkQueue *Q, int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    QNode *p=(Q->front)->next;
    e=&(p->data);
    (Q->front)->next=p->next;
    if(Q->rear==p)
        Q->rear=Q->front;
    free(p);
    return OK;
}

/*取队头元素*/
int GetHead(LinkQueue *Q)
{
    if(Q->front!=Q->rear)
        return ((Q->front)->next)->data;
}

/*销毁链队列*/
int DestroyQueue(LinkQueue *Q)
{
    while(Q->front)
    {
        Q->rear=(Q->front)->next;
        free(Q->front);
        Q->front=Q->rear;
    }
    return OK;
}

/*判断链队列是否为空*/
bool QueueEmpty(LinkQueue *Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}
