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

void Difference(LinkList La, LinkList Lb, int *n){//求两个链表La和Lb的差集，即求出仅在La中出现而不再Lb中出现的元素
                                                  //La和Lb差集的结果储存在La中，n是结果集合中元素个数，调用时为0
                                                  //关键在于：在遍历链表时，需要保存待删结点的前驱
    LNode *pa=La->next;//pa初始化为La的首元结点
    LNode *pb=Lb->next;//pb初始化为Lb的首元结点
    LNode *pre=La;//pre指向La中pa所指结点的前驱结点

    while(pa&&pb){
        if(pa->data<pb->data){//如果当前pa的data小于pb的data，需要在La中继续向后遍历，寻找跟当前pb相等的结点
            (*n)++;
            pre=pa;
            pa=pa->next;//pa指向La中的下一个结点
        }

        else if(pa->data>pb->data){//如果当前pa的data大于pb的data，则在La中不会再出现跟当前pb相等的结点，因此需要提取Lb中的下一个结点进行比较
            pb=pb->next;//pb指向Lb中的下一个结点
        }

        else{//如果当前pa的data等于pb的data，则删除当前的pa结点
            pre->next=pa->next;
            LNode *u=pa;
            pa=pa->next;
            free(u);
        }
    }
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

    int n=0;
    Difference(La, Lb, &n);
    printf("仅在La中出现而不在Lb中出现的元素为（即La与Lb的差集）：");
    ListTraverse(La);
    printf("\n");
    printf("差集中元素的个数为：%d", n);
}
