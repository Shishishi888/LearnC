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

void MergeList(LinkList La, LinkList Lb, LinkList *Lc){//将两个非递减的有序链表La和Lb合并为一个非递增的有序链表Lc，前插法
    LNode *pa=La->next;//pa初始化为La的首元结点
    LNode *pb=Lb->next;//pb初始化为Lb的首元结点
    *Lc=La;
    LNode *pc=La;
    (*Lc)->next=NULL;

    while(pa||pb){
        if(!pa){//如果pa已经指向La的最后一个结点
            pc=pb;
            pb=pb->next;//pb指向Lb链表中的下一个结点
        }

        else if(!pb){//如果pb已经指向Lb的最后一个结点
            pc=pa;
            pa=pa->next;//pa指向La链表中的下一个结点
        }

        else if(pa->data<=pb->data){//如果pa的data小于或等于pb的data
            pc=pa;//pc指向当前pa和pb中较小的结点，即pa
            pa=pa->next;
        }

        else{//如果pa的data大于pb的data
            pc=pb;//pc指向当前pa和pb中较小的结点，即pb
            pb=pb->next;
        }

        pc->next=(*Lc)->next;//将pc结点插入Lc链表的首部
        (*Lc)->next=pc;
    }

    free(Lb);
}

void main(){
    printf("请先创建递增的单链表La：\n");
    LinkList La;
    InitList(&La);
    CreateList_R(La, 3);
    printf("创建成功！单链表La的遍历结果为：");
    ListTraverse(La);
    printf("\n");

    printf("请先创建递增的单链表Lb：\n");
    LinkList Lb;
    InitList(&Lb);
    CreateList_R(Lb, 6);
    printf("创建成功！单链表Lb的遍历结果为：");
    ListTraverse(Lb);
    printf("\n");

    LinkList Lc;
    MergeList(La, Lb, &Lc);
    printf("合并单链表La和Lb，合并结果为：");
    ListTraverse(Lc);
}
/*
    将两个非递减的有序链表合并为一个非递增的有序链表。要求结果链表仍使用原来的两个
    链表的储存空间，不另外占用其它的储存空间。表中不允许有重复的数据。
*/
