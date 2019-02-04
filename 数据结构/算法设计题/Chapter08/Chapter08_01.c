#include <stdio.h>
#include <malloc.h>
#define MAX 20
#define OK 1
#define ERROR 0

typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//������ĳ�ʼ��
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

void CreateList_R(LinkList *L, int n){//β�巨����������
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    LNode *r=*L;
    int i;
    for(i=0;i<n;++i){
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

void ListTraverse(LinkList L){//����������ı���
    if(!L) exit(0);
    LNode *p=L->next;
    while(p){
        printf("%3d", p->data);
        p=p->next;
    }
}

/*
void SelectSort(LinkList L){ //�Ե�����Ϊ����ṹ�ļ�ѡ�������㷨
	LNode *p=L->next;
	LNode *q=L;
	LNode *tempP;
	LNode *tempQ;
	int count=0; //��¼�����ǵڼ�������
	int max;

	while(p){
		max=p->data;
		while(p){//��δ����Ľ����ѡ�������
			if(p->data>=max){
				max=p->data;
				tempP=p;
				tempQ=q;
			}
			p=p->next;
			q=q->next;
		}

		//����������ѡ�����������뵽��ͷ
		tempQ->next=tempP->next;
		tempP->next=L->next;
		L->next=tempP;

		count++; //һ���������
		int tempCount=count;

		p=L->next;
		q=L;
		while(tempCount--){
			p=p->next;
			q=q->next;
			tempP=p;
			tempQ=q;
		}
	}
}
*/

void SelectSort(LinkList L){ //�Ե�����Ϊ����ṹ�ļ�ѡ�������㷨
	LNode *p=L->next;//pָ����Ԫ���
	while(p!=NULL){
		LNode *q=p->next;
		LNode *r=p;//rָ��ؼ�����С�Ľ��
		while(q!=NULL){
			if(q->data<r->data)
				r=q;
			q=q->next;
		}
		if(r!=p){
			int temp=p->data;
			p->data=r->data;
			r->data=temp;
		}
		p=p->next;
	}
}


void main(){
	LinkList L;
	InitList(&L);
	int n;
	printf("�����������ĵ�����ĳ��ȣ�");
	scanf("%d", &n);
	printf("���������������ĵ������Ԫ�أ�");
	CreateList_R(&L, n);
	printf("����ǰ��");
	ListTraverse(L);
	printf("\n");
	printf("�����");
	SelectSort(L);
	ListTraverse(L);
}

/*
	���Ե�����Ϊ�洢�ṹ��ʵ�ּ�ѡ�������㷨
*/
