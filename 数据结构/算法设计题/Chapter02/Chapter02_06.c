#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//������ĳ�ʼ��
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

void CreateList_R(LinkList L, int n){//��巨����������
    LNode *r=L;
    int i;
    for(i=0;i<n;++i){
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

void ListTraverse(LinkList L){//����������
    if(!L) exit(0);
    LNode *p=L->next;
    while(p){
        printf("%3d", p->data);
        p=p->next;
    }
}

int Max(LinkList L){//�������е������
    int max=0;
    LNode *p=L->next;
    while(p){
        if(p->data>max)
            max=p->data;
        p=p->next;
    }
    return max;
}

/*
int Max(LinkList L){//�������е������
    if(L->next==NULL)
        return NULL;
    LNode *pmax=L->next;
    LNode *p=L->next->next;
    while(p!=NULL){
        if(p->data>pmax->data)
            pmax=p;
        p=p->next;
    }

    return pmax->data;
}
*/

void main(){
    printf("���ȴ��������ĵ�����L��\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("�����ɹ���������L�ı������Ϊ��");
    ListTraverse(L);
    printf("\n");

    printf("������L�����Ľ��Ϊ��%d", Max(L));
}

/*
    ���һ���㷨��ͨ��һ�˱���ȷ������Ϊn�ĵ�������ֵ���Ľ��
*/
