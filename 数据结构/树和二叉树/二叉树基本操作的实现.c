#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX 20
#define OK 1
#define ERROR 0

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*先序遍历的顺序建立二叉树*/
BiTree CreateBiTree(BiTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

/*层次遍历输出*/
void LevelOrder(BiTree T)
{
    BiTree Queue[MAX], b;
    int front, rear;
    front=rear=0;
    if(T)
    {
        Queue[rear++]=T;
        while(front!=rear)
        {
            b=Queue[front++];
            printf("%2c",b->data);
            if(b->lchild!=NULL) Queue[rear++]=b->lchild;
            if(b->rchild!=NULL) Queue[rear++]=b->rchild;
        }
    }
}

/*先序遍历二叉树*/
void PreOrderTraverse(BiTree T)
{
    if(T)
    {
        printf("%2c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

/*中序遍历二叉树*/
void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%2c",T->data);
        InOrderTraverse(T->rchild);
    }
}

/*后序遍历二叉树*/
void PostOrderTraverse(BiTree T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%2c",T->data);
    }
}
/*复制二叉树*/
void Copy(BiTree T, BiTree *NewT)
{
    if(T==NULL)
    {
        *NewT=NULL;
        return;
    }
    else
    {
        *NewT=(BiTNode *)malloc(sizeof(BiTNode));
        (*NewT)->data=T->data;
        Copy(T->lchild, &((*NewT)->lchild));
        Copy(T->rchild, &((*NewT)->rchild));
    }
}

/*计算二叉树的深度*/
int Depth(BiTree T)
{
    if(T==NULL)
        return 0;
    else
    {
        int m=Depth(T->lchild);
        int n=Depth(T->rchild);
        if(m>n)
            return m+1;
        else
            return n+1;
    }
}

/*统计二叉树中结点的个数*/
int NodeCount(BiTree T)
{
    if(T==NULL)
        return 0;
    else
        return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
}

/*统计二叉树中叶子结点的个数*/
int LeafCount(BiTree T)
{
    if(T==NULL)
        return 0;
    else if(T->lchild==NULL&&T->rchild==NULL)
        return 1;
    else
        return LeafCount(T->lchild)+LeafCount(T->rchild);
}

/*主程序*/
void main()
{
    BiTree T=NULL;
    printf("*******************采用递归函数构造第一棵二叉树*******************\n");
    printf("请输入构造二叉树的字符序列：");
    if(T=CreateBiTree(&T))
    {
        printf("二叉树建立成功！\n");
        printf("层序遍历输出二叉树:\n");
        LevelOrder(T);
        printf("\n");

        printf("先序遍历输出二叉树:\n");
        PreOrderTraverse(T);
        printf("\n");

        printf("中序遍历输出二叉树:\n");
        InOrderTraverse(T);
        printf("\n");

        printf("后序遍历输出二叉树:\n");
        PostOrderTraverse(T);
        printf("\n");

        printf("复制该二叉树\n");
        BiTree NewT;
        Copy(T, &NewT);
        printf("复制成功！复制结果为（先序遍历输出复制二叉树）：\n");
        PreOrderTraverse(NewT);
        printf("\n");

        printf("该二叉树的深度为：");
        printf("%d\n",Depth(T));

        printf("该二叉树的结点个数为：");
        printf("%d\n",NodeCount(T));

        printf("该二叉树的叶子结点个数为：");
        printf("%d\n",LeafCount(T));

    }
    else
        printf("很遗憾，不能成功建立二叉树！！！\n");
}
