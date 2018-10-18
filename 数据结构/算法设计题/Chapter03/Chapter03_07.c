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

int InitQueue(SqQueue *S){//ѭ�����еĳ�ʼ��
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    S->front=S->rear=0;
    S->tag=0;
    S->queuesize=MAXSIZE;
}

int EnQueue(SqQueue *S, SElemType e){//���
    if(S->tag==1&&S->front==S->rear)//���tag=1��˵����һ����ɵ�����Ӳ���
        return ERROR;
    S->base[S->rear]=e;
    S->rear=(S->rear+1)%S->queuesize;
    if(S->tag==0)
        S->tag=1;//tag=1��˵�����ڽ�����Ӳ���
    return OK;
}

int DeQueue(SqQueue *S, SElemType *x){//����
    if(S->tag==0&&S->front==S->rear)//���tag=0��˵����һ����ɵ��ǳ��Ӳ���
        return ERROR;
    *x=S->base[S->front];
    S->front=(S->front+1)%S->queuesize;
    if(S->tag==1)
        S->tag=0;//tag=1��˵�����ڽ��г��Ӳ���
    return OK;
}

int IsEmpty(SqQueue *S){//�ӿ�
    return S->tag==0&&S->front==S->rear;
}

int IsFull(SqQueue *S){//����
    return S->tag==1&&S->front==S->rear;
}

void main(){
    SqQueue sqQueue;
    InitQueue(&sqQueue);

    if(IsEmpty(&sqQueue)) printf("��ѭ������Ϊ�գ�\n");
    else                  printf("��ѭ�����в�Ϊ�գ�\n");
    EnQueue(&sqQueue, 1);
    if(IsEmpty(&sqQueue)) printf("��ѭ������Ϊ�գ�\n");
    else                  printf("��ѭ�����в�Ϊ�գ�\n");
    EnQueue(&sqQueue, 2);
    EnQueue(&sqQueue, 3);
    EnQueue(&sqQueue, 4);
    EnQueue(&sqQueue, 5);
    EnQueue(&sqQueue, 6);
    EnQueue(&sqQueue, 7);
    EnQueue(&sqQueue, 8);
    EnQueue(&sqQueue, 9);
    if(IsFull(&sqQueue)) printf("��ѭ������������\n");
    else                 printf("��ѭ������δ����\n");
    EnQueue(&sqQueue, 10);
    if(IsFull(&sqQueue)) printf("��ѭ������������\n");
    else                 printf("��ѭ������δ����\n");

    int x;
    DeQueue(&sqQueue, &x);
    printf(                     "���ӳɹ�������Ԫ��Ϊ��%d\n", x);
    if(IsFull(&sqQueue)) printf("��ѭ������������\n");
    else                 printf("��ѭ������δ����\n");
}

/*
    ����������Q[m]���ѭ�������е�Ԫ�أ�ͬʱ����һ����־tag����tag==0��tag==1�������ڶ�ͷָ�루front��
    �Ͷ�βָ�루rear�����ʱ������״̬Ϊ���ա����ǡ��������Ա�д��˽ṹ��Ӧ�Ĳ��루enqueue����ɾ����dequeue��
    �㷨��
*/
