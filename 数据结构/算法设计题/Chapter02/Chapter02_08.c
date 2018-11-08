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

/*
void DeleteMinMax(LinkList L, int min, int max){//删除递增有序单链表中指定范围的结点
    LNode *p=L->next;//p初始化为链表L的首元结点
    LNode *q=L;

    while(p){
        if(p->data>min&&p->data<max){
            q->next=p->next;
            free(p);//删除当前的p结点
            p=q->next;//p指向当前的下一个结点
        }
        else{
            p=p->next;
            q=q->next;
        }
    }
}
*/

void DeleteMinMax(LinkList L, int min, int max){//删除递增有序单链表中指定范围的结点
    LNode *p=L->next;//p初始化为链表L的首元结点
    LNode *pre;

    while(p&&p->data<=min){//查找到第一个值大于min的结点
        pre=p;//pre指向当前的p结点
        p=p->next;//p指向当前的下一个结点
    }

    while(p&&p->data<max){//查找到第一个值大于等于max的结点
        p=p->next;//p指向当前的下一个结点
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
    printf("请先创建一个递增的单链表L：\n");
    LinkList L;
    InitList(&L);
    CreateList_R(L, 6);
    printf("创建成功！单链表L的遍历结果为：");
    ListTraverse(L);
    printf("\n");

    printf("删除单链表L中在区间[2,5]的结点，删除后的L为：");
    DeleteMinMax(L, 2, 5);
    ListTraverse(L);
}

/*
    设计一个算法，删除递增有序链表中值大于mink且小于maxk的所有元素（mink和maxk是给定的两个参数，其值可以
    和表中的元素相同，也可以不同）
*/
