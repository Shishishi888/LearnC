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

int LeafNode(BiTree T){//统计二叉树结点的个数
    if(T==NULL) return 0;
    else return LeafNode(T->lchild)+LeafNode(T->rchild)+1;
}

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：\n");
    T=CreateBiTree(&T);
    printf("二叉树创建成功！\n");
    printf("该二叉树结点的个数为：%d\n", LeafNode(T));
}

/*
    统计二叉树结点的个数
*/
