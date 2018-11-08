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

void MergeList(LinkList La, LinkList Lb, LinkList *Lc){//��������������������La��Lb�ϲ�Ϊһ����������������Lc��β�巨
    LNode *pa=La->next;//pa��ʼ��ΪLa����Ԫ���
    LNode *pb=Lb->next;//pb��ʼ��ΪLb����Ԫ���
    *Lc=La;
    LNode *pc=La;

    while(pa&&pb){
        if(pa->data<pb->data){//�����ǰpa��dataС��pb��data
            pc->next=pa;
            pc=pa;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pa
            pa=pa->next;//paָ��La�����е���һ�����
        }

        else if(pa->data>pb->data){//�����ǰpa��data����pb��data
            pc->next=pb;
            pc=pb;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pb
            pb=pb->next;//pbָ��Lb�����е���һ�����

        }

        else{//���pa��data����pb��data
            pc->next=pa;
            pc=pa;
            pa=pa->next;

            LNode *q=pb->next;
            free(pb);//ɾ��pb
            pb=q;
        }

        pc->next=pa?pa:pb;//���ǿ������ʣ����ֱ�����ӵ�Lc��������
        free(Lb);
    }
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
    ��������������������ϲ�Ϊһ����������������Ҫ����������ʹ��ԭ��������
    ����Ĵ���ռ䣬������ռ�������Ĵ���ռ䡣���в��������ظ������ݡ�
*/
