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

void Decompose(LinkList La, LinkList *Lb, LinkList *Lc){//分解单链表
    *Lb=(LNode *)malloc(sizeof(LNode));
    *Lc=(LNode *)malloc(sizeof(LNode));
    (*Lb)->next=NULL;
    (*Lc)->next=NULL;

    LNode *p=La->next;
    LNode *r=p->next;//暂存p的后继结点

    while(p){
        r=p->next;

        if(p->data<0){//如果p的data小于0
            //将p插入到链表Lb的首部
            p->next=(*Lb)->next;
            (*Lb)->next=p;
        }

        else if(p->data>0){//如果p的data大于0
            //将p插入到链表Lc的首部
            p->next=(*Lc)->next;
            (*Lc)->next=p;
        }

        p=r;//p指向新的待处理的结点
    }
}
/*
void Decompose(LinkList La, LinkList Lb, LinkList Lc){//分解单链表La
    LNode *pa=La->next;
    LNode *pb=Lb;
    LNode *pc=Lc;

    while(pa){
        if(pa->data<0){
            pb->next=pa;
            pb=pb->next;
            pa=pa->next;
            pb->next=NULL;
        }

        else if(pa->data>0){
            pc->next=pa;
            pc=pc->next;
            pa=pa->next;
            pc->next=NULL;
        }
    }
}
*/

void main(){
    printf("请先创建递增的单链表La：\n");
    LinkList La;
    InitList(&La);
    CreateList_R(La, 6);
    printf("创建成功！单链表La的遍历结果为：");
    ListTraverse(La);
    printf("\n");


    LinkList Lb;
    LinkList Lc;
    printf("将单链表La分解为Lb和Lc（其中，Lb的结点小于0，Lc的结点大于0），结果为：\n");
    Decompose(La, &Lb, &Lc);

    printf("Lb:");
    ListTraverse(Lb);
    printf("\n");

    printf("Lc:");
    ListTraverse(Lc);
    printf("\n");

    /*
    LinkList Lb;
    LinkList Lc;
    InitList(&Lb);
    InitList(&Lc);
    printf("将单链表La分解为Lb和Lc（其中，Lb的结点小于0，Lc的结点大于0），结果为：\n");
    Decompose(La, Lb, Lc);

    printf("Lb:");
    ListTraverse(Lb);
    printf("\n");

    printf("Lc:");
    ListTraverse(Lc);
    printf("\n");
    */
}

/*
    设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B和C，其中B表的结点为A表中
    值小于零的结点，而C表的结点为A表中值大于零的结点（链表A中的元素为非零整数，要求B、C表
    利用A表的结点）。
*/
