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

void Difference(LinkList La, LinkList Lb, int *n){//����������La��Lb�Ĳ�����������La�г��ֶ�����Lb�г��ֵ�Ԫ��
                                                  //La��Lb��Ľ��������La�У�n�ǽ��������Ԫ�ظ���������ʱΪ0
                                                  //�ؼ����ڣ��ڱ�������ʱ����Ҫ�����ɾ����ǰ��
    LNode *pa=La->next;//pa��ʼ��ΪLa����Ԫ���
    LNode *pb=Lb->next;//pb��ʼ��ΪLb����Ԫ���
    LNode *pre=La;//preָ��La��pa��ָ����ǰ�����

    while(pa&&pb){
        if(pa->data<pb->data){//�����ǰpa��dataС��pb��data����Ҫ��La�м�����������Ѱ�Ҹ���ǰpb��ȵĽ��
            (*n)++;
            pre=pa;
            pa=pa->next;//paָ��La�е���һ�����
        }

        else if(pa->data>pb->data){//�����ǰpa��data����pb��data������La�в����ٳ��ָ���ǰpb��ȵĽ�㣬�����Ҫ��ȡLb�е���һ�������бȽ�
            pb=pb->next;//pbָ��Lb�е���һ�����
        }

        else{//�����ǰpa��data����pb��data����ɾ����ǰ��pa���
            pre->next=pa->next;
            LNode *u=pa;
            pa=pa->next;
            free(u);
        }
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

    int n=0;
    Difference(La, Lb, &n);
    printf("����La�г��ֶ�����Lb�г��ֵ�Ԫ��Ϊ����La��Lb�Ĳ����");
    ListTraverse(La);
    printf("\n");
    printf("���Ԫ�صĸ���Ϊ��%d", n);
}
