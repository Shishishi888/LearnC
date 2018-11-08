#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct DuLNode
{
    int data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

void Exchange(DuLNode *p){//交换双向链表中，p所指向的结点及其前驱结点的位置
    DuLNode *q=p->prior;//q指向p的前驱结点
    q->prior->next=p;
    p->prior=q->prior;
    q->next=p->next;
    q->prior=p;
    p->next->prior=q;
    p->next=q;
}

/*
    已知p指向双向循环链表中的一个结点，其结点结构为data、prior、next三个域，写出算法change(p)，交换
    p所指向的结点及其前驱结点的位置
*/
