#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 10
typedef int QElemType;

typedef struct{
    QElemType *base;
    int front;
    int rear;
    int queuesize;
}SqQueue;

int InitQueue(SqQueue *Q){//初始化循环队列
    Q->queuesize=MAXSIZE;
    Q->base=(QElemType *)malloc(sizeof(QElemType)*Q->queuesize);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, QElemType e){//从队首插入，队首浪费一个储存空间
    if(IsFull(Q))
        return ERROR;
    Q->base[Q->front]=e;
    Q->front=(Q->front-1+Q->queuesize)%Q->queuesize;
    return OK;
}

int DeQueue(SqQueue *Q, QElemType *e){//从队尾删除
    if(IsEmpty(Q))
        return ERROR;
    *e=Q->base[Q->rear];
    Q->rear=(Q->rear-1+Q->queuesize)%Q->queuesize;
}

int IsEmpty(SqQueue *Q){//判断循环队列是否为空
    return Q->rear==Q->front;
}

int IsFull(SqQueue *Q){//判断循环队列是否已满
    return Q->rear==(Q->front-1+Q->queuesize)%Q->queuesize;
}

void main(){
    SqQueue queue;
    InitQueue(&queue);

    if(IsEmpty(&queue)) printf("该循环队列为空！\n");
    else                printf("该循环队列不为空！\n");

    EnQueue(&queue, 1);

    if(IsEmpty(&queue)) printf("该循环队列为空！\n");
    else                printf("该循环队列不为空！\n");

    EnQueue(&queue, 2);
    EnQueue(&queue, 3);
    EnQueue(&queue, 4);
    EnQueue(&queue, 5);
    EnQueue(&queue, 6);
    EnQueue(&queue, 7);
    EnQueue(&queue, 8);

    if(IsFull(&queue)) printf("该循环队列已满！\n");
    else                printf("该循环队列未满！\n");

    EnQueue(&queue, 9);//队首浪费一个储存空间
    if(IsFull(&queue)) printf("该循环队列已满！\n");
    else                printf("该循环队列未满！\n");

    int x;
    DeQueue(&queue, &x);
    printf("出队成功！出队元素为：%d\n", x);
    if(IsFull(&queue)) printf("该循环队列已满！\n");
    else                printf("该循环队列未满！\n");
}

/*
    如果允许在循环队列的两端都可以进行插入和删除操作。要求：
    1.写出循环队列的类型定义
    2.写出“从队尾删除”和“从队头插入”的算法
*/
