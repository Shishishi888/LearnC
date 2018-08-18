#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct BiThrNode
{
    char data;
    struct BiThrNode *lchild, *rchild;
    int LTag, RTag;
}BiThrNode, *BiThrTree;

/*先序遍历构造线索二叉树*/
BiThrTree CreateBiTree(BiThrTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiThrNode *)malloc(sizeof(BiThrNode));
        (*T)->data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

BiThrTree pre;

/*以结点P为根的子树中序线索化*/
void InThreading(BiThrTree p)
{
    if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->LTag=1;
            p->lchild=pre;
        }
        else
            p->LTag=0;
        if(!pre->rchild)
        {
            pre->RTag=1;
            pre->rchild=p;
        }
        else
            pre->RTag=0;
        pre=p;
        InThreading(p->rchild);
    }
}

/*带头结点的二叉树中序线索化*/
BiThrTree InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt=(BiThrNode *)malloc(sizeof(BiThrNode));
    if(!(*Thrt)) exit(0);
    (*Thrt)->LTag=0;
    (*Thrt)->RTag=1;
    (*Thrt)->rchild=*Thrt;
    if(!T)
        (*Thrt)->lchild=*Thrt;
    else
    {
        (*Thrt)->lchild=T;
        pre=*Thrt;
        InThreading(T);
        pre->rchild=*Thrt;
        pre->RTag=1;
        (*Thrt)->rchild=pre;
    }
    return *Thrt;
}

/*遍历中序线索二叉树*/
void InOrderTraverse_Thr(BiThrTree T)                          //T指向头结点，头结点的左键lchild指向根结点
{
    BiThrTree p=T->lchild;                                     //p指向根结点
    while(p!=T)
    {
        while(p->LTag==0) p=p->lchild;                         //沿左孩子向下
        printf("%3c",p->data);                                 //访问左子树为空的结点
        while(p->RTag==1&&p->rchild!=T)
        {
            p=p->rchild;                                       //沿右线索访问后继结点
            printf("%3c", p->data);
        }
        p=p->rchild;                                           //转向p的右子树
    }
}

void main()
{
    BiThrTree T=NULL, Thrt=NULL;
    printf("***********************构造一棵二叉树并对其进行遍历***********************\n");
    printf("请输入构造二叉树的字符序列：");
    T=CreateBiTree(&T);
    if(T)
    {
        printf("线索链表表示的二叉树构造成功！\n");
        printf("下面进行中序遍历线索化\n");
        Thrt=InOrderThreading(&Thrt, T);
        printf("中序遍历线索化二叉树：");
        InOrderTraverse_Thr(Thrt);
    }
    else
    {
        printf("线索链表表示的二叉树构造不成功！\n");
    }
}

