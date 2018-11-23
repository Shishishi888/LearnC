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

void Inverse(LinkList L){//��ת������
    LNode *p=L->next;//p��ʼ��Ϊ��Ԫ���
    LNode *q;
    L->next=NULL;

    while(p){
        q=p->next;//qָ��ǰp����һ�����

        //ͷ�巨
        p->next=L->next;
        L->next=p;
        p=q;//pָ��ǰ����һ�����
    }
}

void main(){
    printf("���ȴ��������ĵ�����L��\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("�����ɹ���������L�ı������Ϊ��");
    ListTraverse(L);
    printf("\n");

    printf("��ת������L����ת���Ϊ��");
    Inverse(L);
    ListTraverse(L);
}

/*
	���һ���㷨�������������н������ӷ���ԭ�ء���ת����Ҫ������ԭ���
	����ռ䣬���仰˵��Ҫ���㷨�Ŀռ临�Ӷ�ΪO(1)��
*/