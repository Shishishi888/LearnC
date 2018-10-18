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

int InitQueue(LinkQueue *Q){//���еĳ�ʼ��
    Q->rear=(QNode *)malloc(sizeof(QNode));//����ͷ���
    if(!Q->rear)
        exit(0);
    Q->rear->next=Q->rear;//ͷ����е�nextָ����
    return OK;
}

int EmptyQueue(LinkQueue *Q){//�ж϶����Ƿ�Ϊ��
    return Q->rear==Q->rear->next;//�ж϶�βָ���Ƿ�ָ��ͷ���
}

int EnQueue(LinkQueue *Q, QElemType e){//����
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=Q->rear->next;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, int *e){//����
     if(EmptyQueue(Q))
        return ERROR;
     QNode *p=Q->rear->next->next;//ָ��pָ����׽��
     *e=p->data;
     if(p==Q->rear){//������׽����ڶ�β��㣬��������ֻ��һ��Ԫ��
        Q->rear=Q->rear->next;//��βָ��ָ��ͷ���
        Q->rear->next=p->next;//ͷ����е�nextָ���µĶ��׽��
     }

     else
        Q->rear->next->next=p->next;//ͷ����е�nextָ���µĶ��׽��
     free(p);
     return OK;
}

/*
void InitQueue(LinkQueue *Q){//���еĳ�ʼ�����ÿն���
    Q->rear=(QNode *)malloc(sizeof(QNode));//ͷ���
    if(!Q->rear)
        exit(0);
    Q->rear->next=Q->rear;

//    Q->rear=Q->rear->next;//��βָ��ָ��ͷ���
//    while(Q->rear!=Q->rear->next){//���ͷ����е�nextû��ָ���������зǿ�
//        QueuePtr s=Q->rear->next;
//        Q->rear->next=s->next;
//        free(s);
//    }

}

int EmptyQueue(LinkQueue *Q){//�ж϶����Ƿ�Ϊ��
    return Q->rear->next->next==Q->rear->next;//�ж�ͷ����е�next�Ƿ�ָ����
    //Q->rear����βָ��
    //Q->rear->next����β����е�next��ָ��ͷ���
    //Q->rear->next->next��ͷ����е�next��������Ϊ��ʱ��ָ����
    //                                     ������Ϊ�ǿ�ʱ��ָ����׽��
}

int EnQueue(LinkQueue *Q, int e){//����
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=Q->rear->next;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e){//����
    if(EmptyQueue(Q))
        return ERROR;

    QNode *p=Q->rear->next->next;//pָ����׽��
    *e=p->data;
    if(p==Q->rear){//������׽����ڶ�β��㣬��������ֻ��һ��Ԫ��
        Q->rear=Q->rear->next;//��βָ��ָ��ͷ���
        Q->rear->next=p->next;//ͷ����е�nextָ����
    }
    else
        Q->rear->next->next=p->next;
    free(p);
    return OK;
}
*/

void main(){
    LinkQueue queue;
    InitQueue(&queue); printf("���г�ʼ���ɹ���\n");
    if(EmptyQueue(&queue)) printf("�ö���Ϊ�գ�\n");
    else           printf("�ö��зǿգ�\n");

    EnQueue(&queue, 1); printf("��ӳɹ������Ԫ��Ϊ1\n");
    EnQueue(&queue, 2); printf("��ӳɹ������Ԫ��Ϊ2\n");
    EnQueue(&queue, 3); printf("��ӳɹ������Ԫ��Ϊ3\n");
    EnQueue(&queue, 4); printf("��ӳɹ������Ԫ��Ϊ4\n");
    if(EmptyQueue(&queue)) printf("�ö���Ϊ�գ�\n");
    else           printf("�ö��зǿգ�\n");

    int x;
    DeQueue(&queue, &x);  printf("���ӳɹ�������Ԫ��Ϊ%d\n", x);
    DeQueue(&queue, &x);  printf("���ӳɹ�������Ԫ��Ϊ%d\n", x);
    DeQueue(&queue, &x);  printf("���ӳɹ�������Ԫ��Ϊ%d\n", x);
    if(EmptyQueue(&queue)) printf("�ö���Ϊ�գ�\n");
    else           printf("�ö��зǿգ�\n");
    DeQueue(&queue, &x);  printf("���ӳɹ�������Ԫ��Ϊ%d\n", x);
    if(EmptyQueue(&queue)) printf("�ö���Ϊ�գ�\n");
    else           printf("�ö��зǿգ�\n");
}

/*
    �����Դ�ͷ����ѭ�������ʾ���У�����ֻ��һ��ָ��ָ���βԪ�ؽ�㣨ע�⣺����ͷָ�룩��
    �Ա�д��Ӧ���ÿն��С��ж϶����Ƿ�Ϊ�ա���Ӻͳ��ӵ��㷨
*/
