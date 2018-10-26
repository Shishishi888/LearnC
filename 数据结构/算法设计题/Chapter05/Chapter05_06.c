#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OK 1
#define ERROR 0

/********************������********************/
typedef struct BiTNode{//�������Ķ�������洢��ʾ
    char tree_data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//���򴴽�������
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

/*********************����*********************/
typedef BiTNode QElemType;
typedef struct QNode{//���е���ʽ�洢�ṹ
    QElemType queue_data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue *Q){//���ӵĳ�ʼ��
    Q->front=Q->rear=(QNode *)malloc(sizeof(QNode));
    Q->front->next=NULL;
    return OK;
}

int EnQueue(LinkQueue *Q, QElemType e){//���ӵ����
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->queue_data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e){//���ӵĳ���
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

bool QueueEmpty(LinkQueue *Q){//�ж��������Ƿ�Ϊ��
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}

/**********************************************/
int LevelTraverse(BiTree T){//�ǵݹ��α���������
    int num=0;//��¼�������ж�Ϊ1�Ľ��ĸ���
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
    printf("�����򴴽�һ�ö�������");
    CreateBiTree(&T);
    printf("�����������ɹ���\n");
    printf("��α����ö����������Ϊ��");
    int num=LevelTraverse(T);
    printf("\n");
    printf("�ö�������Ϊ1�Ľ��ĸ���Ϊ��%d", num);
}

/*
    �ð����˳������������ķ�����ͳ�����ж�Ϊ1�Ľ��ĸ���
*/
