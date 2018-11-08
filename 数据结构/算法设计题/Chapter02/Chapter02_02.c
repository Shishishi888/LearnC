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

void MergeList(LinkList La, LinkList Lb, LinkList *Lc){//�������ǵݼ�����������La��Lb�ϲ�Ϊһ���ǵ�������������Lc��ǰ�巨
    LNode *pa=La->next;//pa��ʼ��ΪLa����Ԫ���
    LNode *pb=Lb->next;//pb��ʼ��ΪLb����Ԫ���
    *Lc=La;
    LNode *pc=La;
    (*Lc)->next=NULL;

    while(pa||pb){
        if(!pa){//���pa�Ѿ�ָ��La�����һ�����
            pc=pb;
            pb=pb->next;//pbָ��Lb�����е���һ�����
        }

        else if(!pb){//���pb�Ѿ�ָ��Lb�����һ�����
            pc=pa;
            pa=pa->next;//paָ��La�����е���һ�����
        }

        else if(pa->data<=pb->data){//���pa��dataС�ڻ����pb��data
            pc=pa;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pa
            pa=pa->next;
        }

        else{//���pa��data����pb��data
            pc=pb;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pb
            pb=pb->next;
        }

        pc->next=(*Lc)->next;//��pc������Lc������ײ�
        (*Lc)->next=pc;
    }

    free(Lb);
}

void main(){
    printf("���ȴ��������ĵ�����La��\n");
    LinkList La;
    InitList(&La);
    CreateList_R(La, 3);
    printf("�����ɹ���������La�ı������Ϊ��");
    ListTraverse(La);
    printf("\n");

    printf("���ȴ��������ĵ�����Lb��\n");
    LinkList Lb;
    InitList(&Lb);
    CreateList_R(Lb, 6);
    printf("�����ɹ���������Lb�ı������Ϊ��");
    ListTraverse(Lb);
    printf("\n");

    LinkList Lc;
    MergeList(La, Lb, &Lc);
    printf("�ϲ�������La��Lb���ϲ����Ϊ��");
    ListTraverse(Lc);
}
/*
    �������ǵݼ�����������ϲ�Ϊһ���ǵ�������������Ҫ����������ʹ��ԭ��������
    ����Ĵ���ռ䣬������ռ�������Ĵ���ռ䡣���в��������ظ������ݡ�
*/
