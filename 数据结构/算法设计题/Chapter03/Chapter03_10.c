#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//初始化单链表
    *L=(LNode *)malloc(sizeof(LNode));
    if(!(*L))
        exit(0);
    (*L)->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){//从链表首端插入
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetMax(LinkList L){//求链表中的最大整数
    if(!L->next)
        return L->data;
    else{
        int max=GetMax(L->next);
        return max>=L->data?max:L->data;
    }
}

int GetLength(LinkList L){//求链表的结点个数
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

double GetAverage(LinkList L, int n){//求所有整数的平均值
    if(!L->next)
        return L->data;
    else{
        double average=GetAverage(L->next, n-1);
        return (average*(n-1)+L->data)/n;
    }
}
/*
int InitList(LinkList L){
    //L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){//从链表首端插入
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}
*/
void main(){
    LinkList f;
    InitList(&f);

    ListInsert(f, 5);
    ListInsert(f, 19);
    ListInsert(f, 15);
    ListInsert(f, 7);
    ListInsert(f, 12);

    printf("链表中的最大整数为：%d\n", GetMax(f->next));
    printf("链表的结点个数为：%d\n", GetLength(f->next));
    printf("链表的中所有整数的平均值：%2f\n", GetAverage(f->next, GetLength(f->next)));
}

/*
    已知f为单链表的表头指针，链表中储存的都是整形数据，试写出实现下列运算的递归算法：
    1.求链表中的最大整数
    2.求链表的节点个数
    3.求所有整数的平均值
*/

/*
#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode;

int InitList(LNode *L){
                       //因为在主函数中，系统已经为头结点node申请了内存空间
                       //因此在初始化函数中，不需要手动申请（即不需要malloc）
                       //因此不会涉及到对一级指针的修改
                       //因此不需要向初始化函数传递相应的二级指针
    L->next=NULL;
    return OK;
}

int ListInsert(LNode *L, int e){
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetLength(LNode *L){
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

void main(){
    LNode node;//声明一个普通变量node，作为头结点
               //系统会自动为node申请内存空间，不需要手动申请（即不需要malloc）

    InitList(&node);//传入头结点node的地址，即传入指向node的一级指针
    ListInsert(&node, 1);
    ListInsert(&node, 2);
    ListInsert(&node, 2);
    printf("该链表的结点个数为：%d", GetLength((&node)->next));
}

------------------------------------------------------------------------------------------------------------------

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//因为在主函数中，系统未自动为指针node申请其指向的内存空间（即存放头结点的内存空间）
                          //因此在初始化函数中，需要手动申请（即需要malloc）
                          //因此涉及到了对一级指针node的修改
                          //因此需要向初始化函数传递相应的二级指针
    *L=(LNode *)malloc(sizeof(LNode));
    if(!L)
        exit(0);
    (*L)->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){
    LinkList s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetLength(LinkList L){
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

void main(){
    LinkList node;//声明一个指针变量node，指向头结点
                  //系统不会为node申请其指向的内存空间，需要手动申请（即需要malloc，而malloc一般放在初始化函数中）

    InitList(&node);//传入指针node的地址，即传入相应的二级指针
    ListInsert(node, 1);
    ListInsert(node, 2);
    ListInsert(node, 2);
    printf("该链表的结点个数为：%d", GetLength(node->next));
}
*/
