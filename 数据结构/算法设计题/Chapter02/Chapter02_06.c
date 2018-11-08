#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//单链表的初始化
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

void CreateList_R(LinkList L, int n){//后插法创建单链表
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

void ListTraverse(LinkList L){//遍历单链表
    if(!L) exit(0);
    LNode *p=L->next;
    while(p){
        printf("%3d", p->data);
        p=p->next;
    }
}

int Max(LinkList L){//求单链表中的最大结点
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
int Max(LinkList L){//求单链表中的最大结点
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
    printf("请先创建递增的单链表L：\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("创建成功！单链表L的遍历结果为：");
    ListTraverse(L);
    printf("\n");

    printf("单链表L中最大的结点为：%d", Max(L));
}

/*
    设计一个算法，通过一趟遍历确定长度为n的单链表中值最大的结点
*/
