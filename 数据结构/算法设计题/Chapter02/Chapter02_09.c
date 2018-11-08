#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct DuLNode
{
    int data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

void Exchange(DuLNode *p){//����˫�������У�p��ָ��Ľ�㼰��ǰ������λ��
    DuLNode *q=p->prior;//qָ��p��ǰ�����
    q->prior->next=p;
    p->prior=q->prior;
    q->next=p->next;
    q->prior=p;
    p->next->prior=q;
    p->next=q;
}

/*
    ��֪pָ��˫��ѭ�������е�һ����㣬����ṹΪdata��prior��next������д���㷨change(p)������
    p��ָ��Ľ�㼰��ǰ������λ��
*/
