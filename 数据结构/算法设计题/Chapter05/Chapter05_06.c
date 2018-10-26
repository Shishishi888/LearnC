#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OK 1
#define ERROR 0

/********************二叉树********************/
typedef struct BiTNode{//二叉树的二叉链表存储表示
    char tree_data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//先序创建二叉树
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else{
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->tree_data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

/*********************队列*********************/
typedef BiTNode QElemType;
typedef struct QNode{//队列的链式存储结构
    QElemType queue_data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue *Q){//链队的初始化
    Q->front=Q->rear=(QNode *)malloc(sizeof(QNode));
    Q->front->next=NULL;
    return OK;
}

int EnQueue(LinkQueue *Q, QElemType e){//链队的入队
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->queue_data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e){//链队的出队
    if(Q->front==Q->rear)
        return ERROR;
    QNode *p=(Q->front)->next;
    *e=p->queue_data;
    (Q->front)->next=p->next;
    if(Q->rear==p)
        Q->rear=Q->front;
    free(p);
    return OK;
}

bool QueueEmpty(LinkQueue *Q){//判断链队列是否为空
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}

/**********************************************/
int LevelTraverse(BiTree T){//非递归层次遍历二叉树
    int num=0;//记录二叉树中度为1的结点的个数
    if(T){
        LinkQueue queue;
        InitQueue(&queue);

        EnQueue(&queue, *T);

        BiTNode *e;
        while(!QueueEmpty(&queue)){
            DeQueue(&queue, e);
            printf("%2c", e->tree_data);

            if((e->lchild&&!e->rchild)||(!e->lchild&&e->rchild))
                num+=1;

            if(e->lchild) EnQueue(&queue, *(e->lchild));
            if(e->rchild) EnQueue(&queue, *(e->rchild));
        }
    }

    return num;
}

void main(){

    BiTree T;
    printf("请先序创建一棵二叉树：");
    CreateBiTree(&T);
    printf("二叉树创建成功！\n");
    printf("层次遍历该二叉树，结果为：");
    int num=LevelTraverse(T);
    printf("\n");
    printf("该二叉树度为1的结点的个数为：%d", num);
}

/*
    用按层次顺序遍历二叉树的方法，统计树中度为1的结点的个数
*/
