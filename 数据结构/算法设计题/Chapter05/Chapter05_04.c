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

void DoubleTraverse(BiTree T){//双序遍历二叉树
    if(T){
        printf("%2c", T->data);
        DoubleTraverse(T->lchild);
        printf("%2c", T->data);
        DoubleTraverse(T->rchild);
    }
}

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：");
    CreateBiTree(&T);
    printf("二叉树创建成功！\n");
    printf("双序遍历该二叉树，结果为：");
    DoubleTraverse(T);
}

/*
    设计二叉树的双序遍历算法（双序遍历是指对于二叉树的每一个结点来说，先访问这个结点，
    再按双序遍历它的左子树，然后再一次访问这个结点，接下来按双序遍历它的右子树）。
*/
