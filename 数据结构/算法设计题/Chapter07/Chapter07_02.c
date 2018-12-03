#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//创建二叉树（先序）
    int data;
    scanf(" %d",&data);//输入：空格+data
    if(data==-1)
        *T=NULL;
    else{
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->data=data;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

/*
    根据二叉排序树的定义，对二叉树进行递归遍历，左子树的关键字比根结点的关键字小，
    右子树的关键字比根结点的关键字大，一旦有不满足条件则可判定不是二叉排序树。
    通过参数flag的值来判断，flag为1表示是二叉排序树，为0表示为非二叉排序树，flag
    初值为1.设全局指针变量pre，用来指向遍历过程结点的前驱。
    （1）首先递归遍历左子树。
    （2）如果pre为NULL，则使其指向根结点，否则，将当前结点与pre所指的前驱结点作
         比较，如果前驱结点的值小于当前结点的值，则令pre指向当前结点；如果前驱结
         点的值大于当前结点的值，则表示不是二叉排序树，flag置为0。
    （3）最后递归遍历右子树。
*/
int flag=1;//二叉排序树的标志，初始化为1
BiTNode *pre=NULL;//指向前驱结点

int JudgeBST(BiTree T, int *flag){//判断是否为二叉排序树
    if(T&&(*flag)){
        JudgeBST(T->lchild, flag);
        if(pre==NULL)
            pre=T;
        else{
            if(pre->data<T->data) pre=T;
            else *flag=0;
        }
        JudgeBST(T->rchild, flag);
    }
}

void main(){
    printf("请先创建一棵二叉树：\n");
    BiTree T;
    T=CreateBiTree(&T);
    printf("创建二叉树成功!\n");
    JudgeBST(T, &flag);
    if(flag)
        printf("该二叉树是二叉排序树！");
    else
        printf("该二叉树不是二叉排序树！");
}

/*
    试写一个判别给定二叉树是否为二叉排序树的算法
*/
