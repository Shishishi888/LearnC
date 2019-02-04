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

int InitList(LinkList *L){//单链表的初始化
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

void CreateList_R(LinkList *L, int n){//尾插法创建单链表
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

void ListTraverse(LinkList L){//遍历单链表的遍历
    if(!L) exit(0);
    LNode *p=L->next;
    while(p){
        printf("%3d", p->data);
        p=p->next;
    }
}

/*
void SelectSort(LinkList L){ //以单链表为储存结构的简单选择排序算法
	LNode *p=L->next;
	LNode *q=L;
	LNode *tempP;
	LNode *tempQ;
	int count=0; //记录本次是第几趟排序
	int max;

	while(p){
		max=p->data;
		while(p){//从未排序的结点中选出最大结点
			if(p->data>=max){
				max=p->data;
				tempP=p;
				tempQ=q;
			}
			p=p->next;
			q=q->next;
		}

		//将本趟排序选出的最大结点插入到表头
		tempQ->next=tempP->next;
		tempP->next=L->next;
		L->next=tempP;

		count++; //一趟排序完成
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

void SelectSort(LinkList L){ //以单链表为储存结构的简单选择排序算法
	LNode *p=L->next;//p指向首元结点
	while(p!=NULL){
		LNode *q=p->next;
		LNode *r=p;//r指向关键字最小的结点
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
	printf("请输入待排序的单链表的长度：");
	scanf("%d", &n);
	printf("请依次输入待排序的单链表的元素：");
	CreateList_R(&L, n);
	printf("排序前：");
	ListTraverse(L);
	printf("\n");
	printf("排序后：");
	SelectSort(L);
	ListTraverse(L);
}

/*
	试以单链表为存储结构，实现简单选择排序算法
*/
