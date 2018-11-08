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

void Intersection(LinkList La, LinkList Lb, LinkList *Lc){//����������Ľ���
    LNode *pa=La->next;//pa��ʼ��ΪLa�������Ԫ���
    LNode *pb=Lb->next;//pb��ʼ��ΪLb�������Ԫ���

    *Lc=La;
    LNode *pc=La;

    while(pa&&pb){
        if(pa->data==pb->data){//���pa��data����pb��data
            pc->next=pa;
            pc=pa;//pcָ��ǰ��pa���
            pa=pa->next;//paָ��La�����е���һ�����

            //ɾ����ǰ��pb���
            LNode *u=pb;
            pb=pb->next;//pbָ��Lb�����е���һ�����
            free(u);
        }

        else if(pa->data<pb->data){//�����ǰpa��dataС��pb��data����ô������Lb�У�pb֮��Ľ�������pa���������ٳ��ָ�pa��ȵĽ����
                                   //���ֱ��ɾ����ǰ��pa��㼴��
            LNode *u=pa;
            pa=pa->next;//paָ��La�����е���һ�����
            free(u);
        }

        else{//ͬ�������ǰpb��dataС��pa��data����ô������La�У�pa֮��Ľ�������pb���������ٳ��ָ�pb��ȵĽ����
             //���ֱ��ɾ����ǰ��pb��㼴��

             LNode *u=pb;
             pb=pb->next;//pbָ��Lb�����е���һ�����
             free(u);
        }
    }
    while(pa){//����LbΪ�գ�ɾ������La�е�ʣ����
        LNode *u=pa;
        pa=pa->next;//paָ��La�����е���һ�����
        free(u);
    }

     while(pa){//����LaΪ�գ�ɾ������Lb�е�ʣ����
        LNode *u=pb;
        pb=pb->next;//pbָ��Lb�����е���һ�����
        free(u);
    }

    pc->next=NULL;
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
    Intersection(La, Lb, &Lc);
    printf("��������Ľ���Ϊ��");
    ListTraverse(Lc);
}

/*
    ��֪��������A��B�ֱ��ʾ�������ϣ���Ԫ�ص������С�������㷨���������A��B�Ľ�����
    �������A������
*/

