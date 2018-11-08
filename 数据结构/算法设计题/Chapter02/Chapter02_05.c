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

void Decompose(LinkList La, LinkList *Lb, LinkList *Lc){//�ֽⵥ����
    *Lb=(LNode *)malloc(sizeof(LNode));
    *Lc=(LNode *)malloc(sizeof(LNode));
    (*Lb)->next=NULL;
    (*Lc)->next=NULL;

    LNode *p=La->next;
    LNode *r=p->next;//�ݴ�p�ĺ�̽��

    while(p){
        r=p->next;

        if(p->data<0){//���p��dataС��0
            //��p���뵽����Lb���ײ�
            p->next=(*Lb)->next;
            (*Lb)->next=p;
        }

        else if(p->data>0){//���p��data����0
            //��p���뵽����Lc���ײ�
            p->next=(*Lc)->next;
            (*Lc)->next=p;
        }

        p=r;//pָ���µĴ�����Ľ��
    }
}
/*
void Decompose(LinkList La, LinkList Lb, LinkList Lc){//�ֽⵥ����La
    LNode *pa=La->next;
    LNode *pb=Lb;
    LNode *pc=Lc;

    while(pa){
        if(pa->data<0){
            pb->next=pa;
            pb=pb->next;
            pa=pa->next;
            pb->next=NULL;
        }

        else if(pa->data>0){
            pc->next=pa;
            pc=pc->next;
            pa=pa->next;
            pc->next=NULL;
        }
    }
}
*/

void main(){
    printf("���ȴ��������ĵ�����La��\n");
    LinkList La;
    InitList(&La);
    CreateList_R(La, 6);
    printf("�����ɹ���������La�ı������Ϊ��");
    ListTraverse(La);
    printf("\n");


    LinkList Lb;
    LinkList Lc;
    printf("��������La�ֽ�ΪLb��Lc�����У�Lb�Ľ��С��0��Lc�Ľ�����0�������Ϊ��\n");
    Decompose(La, &Lb, &Lc);

    printf("Lb:");
    ListTraverse(Lb);
    printf("\n");

    printf("Lc:");
    ListTraverse(Lc);
    printf("\n");

    /*
    LinkList Lb;
    LinkList Lc;
    InitList(&Lb);
    InitList(&Lc);
    printf("��������La�ֽ�ΪLb��Lc�����У�Lb�Ľ��С��0��Lc�Ľ�����0�������Ϊ��\n");
    Decompose(La, Lb, Lc);

    printf("Lb:");
    ListTraverse(Lb);
    printf("\n");

    printf("Lc:");
    ListTraverse(Lc);
    printf("\n");
    */
}

/*
    ����㷨��һ����ͷ���ĵ�����A�ֽ�Ϊ����������ͬ�ṹ������B��C������B��Ľ��ΪA����
    ֵС����Ľ�㣬��C��Ľ��ΪA����ֵ������Ľ�㣨����A�е�Ԫ��Ϊ����������Ҫ��B��C��
    ����A��Ľ�㣩��
*/
