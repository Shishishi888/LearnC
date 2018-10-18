#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int QElemType;

typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue *Q){//队列的初始化
    Q->rear=(QNode *)malloc(sizeof(QNode));//创造头结点
    if(!Q->rear)
        exit(0);
    Q->rear->next=Q->rear;//头结点中的next指向本身
    return OK;
}

int EmptyQueue(LinkQueue *Q){//判断队列是否为空
    return Q->rear==Q->rear->next;//判断队尾指针是否指向头结点
}

int EnQueue(LinkQueue *Q, QElemType e){//进队
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=Q->rear->next;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, int *e){//出队
     if(EmptyQueue(Q))
        return ERROR;
     QNode *p=Q->rear->next->next;//指针p指向队首结点
     *e=p->data;
     if(p==Q->rear){//如果队首结点等于队尾结点，即队列中只有一个元素
        Q->rear=Q->rear->next;//队尾指针指向头结点
        Q->rear->next=p->next;//头结点中的next指向新的队首结点
     }

     else
        Q->rear->next->next=p->next;//头结点中的next指向新的队首结点
     free(p);
     return OK;
}

/*
void InitQueue(LinkQueue *Q){//队列的初始化，置空队列
    Q->rear=(QNode *)malloc(sizeof(QNode));//头结点
    if(!Q->rear)
        exit(0);
    Q->rear->next=Q->rear;

//    Q->rear=Q->rear->next;//队尾指针指向头结点
//    while(Q->rear!=Q->rear->next){//如果头结点中的next没有指向本身，即队列非空
//        QueuePtr s=Q->rear->next;
//        Q->rear->next=s->next;
//        free(s);
//    }

}

int EmptyQueue(LinkQueue *Q){//判断队列是否为空
    return Q->rear->next->next==Q->rear->next;//判断头结点中的next是否指向本身
    //Q->rear，队尾指针
    //Q->rear->next，队尾结点中的next，指向头结点
    //Q->rear->next->next，头结点中的next，当队列为空时，指向本身
    //                                     当队列为非空时，指向队首结点
}

int EnQueue(LinkQueue *Q, int e){//进队
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=Q->rear->next;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e){//出队
    if(EmptyQueue(Q))
        return ERROR;

    QNode *p=Q->rear->next->next;//p指向队首结点
    *e=p->data;
    if(p==Q->rear){//如果队首结点等于队尾结点，即队列中只有一个元素
        Q->rear=Q->rear->next;//队尾指针指向头结点
        Q->rear->next=p->next;//头结点中的next指向本身
    }
    else
        Q->rear->next->next=p->next;
    free(p);
    return OK;
}
*/

void main(){
    LinkQueue queue;
    InitQueue(&queue); printf("队列初始化成功！\n");
    if(EmptyQueue(&queue)) printf("该队列为空！\n");
    else           printf("该队列非空！\n");

    EnQueue(&queue, 1); printf("入队成功！入队元素为1\n");
    EnQueue(&queue, 2); printf("入队成功！入队元素为2\n");
    EnQueue(&queue, 3); printf("入队成功！入队元素为3\n");
    EnQueue(&queue, 4); printf("入队成功！入队元素为4\n");
    if(EmptyQueue(&queue)) printf("该队列为空！\n");
    else           printf("该队列非空！\n");

    int x;
    DeQueue(&queue, &x);  printf("出队成功！出队元素为%d\n", x);
    DeQueue(&queue, &x);  printf("出队成功！出队元素为%d\n", x);
    DeQueue(&queue, &x);  printf("出队成功！出队元素为%d\n", x);
    if(EmptyQueue(&queue)) printf("该队列为空！\n");
    else           printf("该队列非空！\n");
    DeQueue(&queue, &x);  printf("出队成功！出队元素为%d\n", x);
    if(EmptyQueue(&queue)) printf("该队列为空！\n");
    else           printf("该队列非空！\n");
}

/*
    假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意：不设头指针），
    试编写相应的置空队列、判断队列是否为空、入队和出队等算法
*/
