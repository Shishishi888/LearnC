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

void Inverse(LinkList L){//翻转单链表
    LNode *p=L->next;//p初始化为首元结点
    LNode *q;
    L->next=NULL;

    while(p){
        q=p->next;//q指向当前p的下一个结点

        //头插法
        p->next=L->next;
        L->next=p;
        p=q;//p指向当前的下一个结点
    }
}

void main(){
    printf("请先创建递增的单链表L：\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("创建成功！单链表L的遍历结果为：");
    ListTraverse(L);
    printf("\n");

    printf("翻转单链表L，翻转结果为：");
    Inverse(L);
    ListTraverse(L);
}

/*
	设计一个算法，将链表中所有结点的链接方向“原地”逆转，即要求利用原表的
	储存空间，换句话说，要求算法的空间复杂度为O(1)。
*/