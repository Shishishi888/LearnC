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

void Intersection(LinkList La, LinkList Lb, LinkList *Lc){//求两个链表的交集
    LNode *pa=La->next;//pa初始化为La链表的首元结点
    LNode *pb=Lb->next;//pb初始化为Lb链表的首元结点

    *Lc=La;
    LNode *pc=La;

    while(pa&&pb){
        if(pa->data==pb->data){//如果pa的data等于pb的data
            pc->next=pa;
            pc=pa;//pc指向当前的pa结点
            pa=pa->next;//pa指向La链表中的下一个结点

            //删除当前的pb结点
            LNode *u=pb;
            pb=pb->next;//pb指向Lb链表中的下一个结点
            free(u);
        }

        else if(pa->data<pb->data){//如果当前pa的data小于pb的data，那么在链表Lb中，pb之后的结点均大于pa，即不会再出现跟pa相等的结点了
                                   //因此直接删除当前的pa结点即可
            LNode *u=pa;
            pa=pa->next;//pa指向La链表中的下一个结点
            free(u);
        }

        else{//同理，如果当前pb的data小于pa的data，那么在链表La中，pa之后的结点均大于pb，即不会再出现跟pb相等的结点了
             //因此直接删除当前的pb结点即可

             LNode *u=pb;
             pb=pb->next;//pb指向Lb链表中的下一个结点
             free(u);
        }
    }
    while(pa){//链表Lb为空，删除链表La中的剩余结点
        LNode *u=pa;
        pa=pa->next;//pa指向La链表中的下一个结点
        free(u);
    }

     while(pa){//链表La为空，删除链表Lb中的剩余结点
        LNode *u=pb;
        pb=pb->next;//pb指向Lb链表中的下一个结点
        free(u);
    }

    pc->next=NULL;
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
    Intersection(La, Lb, &Lc);
    printf("两个链表的交集为：");
    ListTraverse(Lc);
}

/*
    已知两个链表A和B分别表示两个集合，其元素递增排列。请设计算法，用于求出A和B的交集，
    并存放在A链表中
*/

