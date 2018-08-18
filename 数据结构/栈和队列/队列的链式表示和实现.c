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

/*���ӵĳ�ʼ��*/
int InitQueue(LinkQueue *Q)
{
    Q->front=Q->rear=(QNode *)malloc(sizeof(QNode));
    Q->front->next=NULL;
    return OK;
}

/*���ӵ����*/
int EnQueue(LinkQueue *Q, int e)
{
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
    return OK;
}

/*���ӵĳ���*/
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

/*ȡ��ͷԪ��*/
int GetHead(LinkQueue *Q)
{
    if(Q->front!=Q->rear)
        return ((Q->front)->next)->data;
}

/*����������*/
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

/*�ж��������Ƿ�Ϊ��*/
bool QueueEmpty(LinkQueue *Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}
