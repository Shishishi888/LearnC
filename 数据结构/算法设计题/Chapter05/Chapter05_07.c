#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//先序创建二叉树
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else{
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

int Depth(BiTree T){//计算二叉树的深度
    if(T==NULL)
        return 0;
    else{
        int m=Depth(T->lchild);
        int n=Depth(T->rchild);
        if(m>n)
            return m+1;
        else
            return n+1;
    }
}

void LongestPath(BiTree T){//输出二叉树中最长路径的结点的值
    if(T){
        printf("%2c", T->data);

        int left=Depth(T->lchild);
        int right=Depth(T->rchild);
        if(left>=right) LongestPath(T->lchild);
        else            LongestPath(T->rchild);
    }
}

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：");
    T=CreateBiTree(&T);
    printf("二叉树创建成功！\n");

    printf("该二叉树的最长路径为：");
    LongestPath(T);
}

/*
    求任意二叉树中第一条最长的路径长度，并输出此路径上各结点的值
*/
