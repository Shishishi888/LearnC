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

/*
void DeleteMinMax(LinkList L, int min, int max){//ɾ����������������ָ����Χ�Ľ��
    LNode *p=L->next;//p��ʼ��Ϊ����L����Ԫ���
    LNode *q=L;

    while(p){
        if(p->data>min&&p->data<max){
            q->next=p->next;
            free(p);//ɾ����ǰ��p���
            p=q->next;//pָ��ǰ����һ�����
        }
        else{
            p=p->next;
            q=q->next;
        }
    }
}
*/

void DeleteMinMax(LinkList L, int min, int max){//ɾ����������������ָ����Χ�Ľ��
    LNode *p=L->next;//p��ʼ��Ϊ����L����Ԫ���
    LNode *pre;

    while(p&&p->data<=min){//���ҵ���һ��ֵ����min�Ľ��
        pre=p;//preָ��ǰ��p���
        p=p->next;//pָ��ǰ����һ�����
    }

    while(p&&p->data<max){//���ҵ���һ��ֵ���ڵ���max�Ľ��
        p=p->next;//pָ��ǰ����һ�����
        LNode *q=pre->next;
        pre->next=p;

        while(p!=q){
            LNode *s=q->next;
            free(q);
            q=s;
        }
    }
}

void main(){
    printf("���ȴ���һ�������ĵ�����L��\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("�����ɹ���������L�ı������Ϊ��");
    ListTraverse(L);
    printf("\n");

    printf("ɾ��������L��������[2,5]�Ľ�㣬ɾ�����LΪ��");
    DeleteMinMax(L, 2, 5);
    ListTraverse(L);
}

/*
    ���һ���㷨��ɾ����������������ֵ����mink��С��maxk������Ԫ�أ�mink��maxk�Ǹ�����������������ֵ����
    �ͱ��е�Ԫ����ͬ��Ҳ���Բ�ͬ��
*/
