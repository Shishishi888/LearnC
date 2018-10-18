#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 10
typedef int SElemType;

typedef struct{
    SElemType *base;
    int front, rear, tag;
    int queuesize
}SqQueue;

int InitQueue(SqQueue *S){//循环队列的初始化
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    S->front=S->rear=0;
    S->tag=0;
    S->queuesize=MAXSIZE;
}

int EnQueue(SqQueue *S, SElemType e){//入队
    if(S->tag==1&&S->front==S->rear)//如果tag=1，说明上一步完成的是入队操作
        return ERROR;
    S->base[S->rear]=e;
    S->rear=(S->rear+1)%S->queuesize;
    if(S->tag==0)
        S->tag=1;//tag=1，说明正在进行入队操作
    return OK;
}

int DeQueue(SqQueue *S, SElemType *x){//出队
    if(S->tag==0&&S->front==S->rear)//如果tag=0，说明上一步完成的是出队操作
        return ERROR;
    *x=S->base[S->front];
    S->front=(S->front+1)%S->queuesize;
    if(S->tag==1)
        S->tag=0;//tag=1，说明正在进行出队操作
    return OK;
}

int IsEmpty(SqQueue *S){//队空
    return S->tag==0&&S->front==S->rear;
}

int IsFull(SqQueue *S){//队满
    return S->tag==1&&S->front==S->rear;
}

void main(){
    SqQueue sqQueue;
    InitQueue(&sqQueue);

    if(IsEmpty(&sqQueue)) printf("该循环队列为空！\n");
    else                  printf("该循环队列不为空！\n");
    EnQueue(&sqQueue, 1);
    if(IsEmpty(&sqQueue)) printf("该循环队列为空！\n");
    else                  printf("该循环队列不为空！\n");
    EnQueue(&sqQueue, 2);
    EnQueue(&sqQueue, 3);
    EnQueue(&sqQueue, 4);
    EnQueue(&sqQueue, 5);
    EnQueue(&sqQueue, 6);
    EnQueue(&sqQueue, 7);
    EnQueue(&sqQueue, 8);
    EnQueue(&sqQueue, 9);
    if(IsFull(&sqQueue)) printf("该循环队列已满！\n");
    else                 printf("该循环队列未满！\n");
    EnQueue(&sqQueue, 10);
    if(IsFull(&sqQueue)) printf("该循环队列已满！\n");
    else                 printf("该循环队列未满！\n");

    int x;
    DeQueue(&sqQueue, &x);
    printf(                     "出队成功！出队元素为：%d\n", x);
    if(IsFull(&sqQueue)) printf("该循环队列已满！\n");
    else                 printf("该循环队列未满！\n");
}

/*
    假设以数组Q[m]存放循环队列中的元素，同时设置一个标志tag，以tag==0和tag==1来区别在队头指针（front）
    和队尾指针（rear）相等时，队列状态为“空”还是“满”。试编写与此结构相应的插入（enqueue）和删除（dequeue）
    算法。
*/
