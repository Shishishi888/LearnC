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

int InitQueue(SqQueue *Q){//��ʼ��ѭ������
    Q->queuesize=MAXSIZE;
    Q->base=(QElemType *)malloc(sizeof(QElemType)*Q->queuesize);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, QElemType e){//�Ӷ��ײ��룬�����˷�һ������ռ�
    if(IsFull(Q))
        return ERROR;
    Q->base[Q->front]=e;
    Q->front=(Q->front-1+Q->queuesize)%Q->queuesize;
    return OK;
}

int DeQueue(SqQueue *Q, QElemType *e){//�Ӷ�βɾ��
    if(IsEmpty(Q))
        return ERROR;
    *e=Q->base[Q->rear];
    Q->rear=(Q->rear-1+Q->queuesize)%Q->queuesize;
}

int IsEmpty(SqQueue *Q){//�ж�ѭ�������Ƿ�Ϊ��
    return Q->rear==Q->front;
}

int IsFull(SqQueue *Q){//�ж�ѭ�������Ƿ�����
    return Q->rear==(Q->front-1+Q->queuesize)%Q->queuesize;
}

void main(){
    SqQueue queue;
    InitQueue(&queue);

    if(IsEmpty(&queue)) printf("��ѭ������Ϊ�գ�\n");
    else                printf("��ѭ�����в�Ϊ�գ�\n");

    EnQueue(&queue, 1);

    if(IsEmpty(&queue)) printf("��ѭ������Ϊ�գ�\n");
    else                printf("��ѭ�����в�Ϊ�գ�\n");

    EnQueue(&queue, 2);
    EnQueue(&queue, 3);
    EnQueue(&queue, 4);
    EnQueue(&queue, 5);
    EnQueue(&queue, 6);
    EnQueue(&queue, 7);
    EnQueue(&queue, 8);

    if(IsFull(&queue)) printf("��ѭ������������\n");
    else                printf("��ѭ������δ����\n");

    EnQueue(&queue, 9);//�����˷�һ������ռ�
    if(IsFull(&queue)) printf("��ѭ������������\n");
    else                printf("��ѭ������δ����\n");

    int x;
    DeQueue(&queue, &x);
    printf("���ӳɹ�������Ԫ��Ϊ��%d\n", x);
    if(IsFull(&queue)) printf("��ѭ������������\n");
    else                printf("��ѭ������δ����\n");
}

/*
    ���������ѭ�����е����˶����Խ��в����ɾ��������Ҫ��
    1.д��ѭ�����е����Ͷ���
    2.д�����Ӷ�βɾ�����͡��Ӷ�ͷ���롱���㷨
*/
