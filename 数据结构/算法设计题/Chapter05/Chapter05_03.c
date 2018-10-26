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

void PreOrderTraverse(BiTree T){//先序遍历二叉树
    if(T){
        printf("%2c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void ChangeLR(BiTree *T){//交换二叉树的左右孩子
    if((*T)->lchild==NULL&&(*T)->rchild==NULL)
        return;
    else{
        BiTNode *p=(*T)->lchild;
        (*T)->lchild=(*T)->rchild;
        (*T)->rchild=p;

    }

    ChangeLR(&((*T)->lchild));
    ChangeLR(&((*T)->rchild));
}

/*
void ChangeLR(BiTree *T){//交换二叉树的左右孩子
    BiTree temp;
    if((*T)->lchild==NULL&&(*T)->rchild==NULL)
        return;
    else{
        temp=(*T)->lchild;
        (*T)->lchild=(*T)->rchild;
        (*T)->rchild=temp;
    }
    ChangeLR(&((*T)->lchild));
    ChangeLR(&((*T)->rchild));
}
*/

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：");
    T=CreateBiTree(&T);
    printf("二叉树创建成功！\n");
    printf("交换该二叉树的左右孩子...\n");
    ChangeLR(&T);
    printf("交换成功！\n");
    printf("交换之后该二叉树为（先序遍历）：");
    PreOrderTraverse(T);
}

/*
    交换二叉树每个结点的左右孩子结点
*/
