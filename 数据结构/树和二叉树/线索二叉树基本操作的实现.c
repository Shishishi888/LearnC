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
{//pre是全局变量，初始化时其右孩子指针为空，便于在树的最左点开始建线索
    if(p)
    {
        InThreading(p->lchild);//左子树递归线索化
        if(!p->lchild)//如果p的左孩子为空
        {
            p->LTag=1;//给p加上左线索
            p->lchild=pre;//p的左孩子指针指向pre（前驱）
        }
        else
            p->LTag=0;
        if(!pre->rchild)//如果pre的右孩子为空
        {
            pre->RTag=1;//给pre加上右线索
            pre->rchild=p;//pre的右孩子指针指向p（后继）
        }
        else
            pre->RTag=0;
        pre=p;//保持pre指向p的前驱
        InThreading(p->rchild);//右子树递归线索化
    }
}

/*带头结点的二叉树中序线索化*/
BiThrTree InOrderThreading(BiThrTree *Thrt, BiThrTree T)//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
{
    *Thrt=(BiThrNode *)malloc(sizeof(BiThrNode));//创建头结点
    (*Thrt)->LTag=0;//头结点有左孩子，若树非空，则其左孩子为树根
    (*Thrt)->RTag=1;//头结点的右孩子指针为右线索
    (*Thrt)->rchild=*Thrt;//初始化时右指针指向自己
    if(!T)//若树为空，则左指针也指向自己
        (*Thrt)->lchild=*Thrt;
    else
    {
        (*Thrt)->lchild=T;//头结点的左孩子指向树根
        pre=*Thrt;//pre初值指向头结点
        InThreading(T);//调用中序线索化算法，对以T为根的二叉树进行中序线索化
        pre->rchild=*Thrt;//中序线索化算法结束后，pre为最右结点，pre的右线索指向头结点
        pre->RTag=1;
        (*Thrt)->rchild=pre;//头结点的右线索指向pre
    }
    return *Thrt;
}

/*遍历中序线索二叉树*/
void InOrderTraverse_Thr(BiThrTree T)                          //T指向头结点，头结点的左孩子lchild指向根结点
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

