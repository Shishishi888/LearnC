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

void AllPath(BiTree T, char path[], int pathlen){//输出二叉树中每个叶子结点到根节点的路径，pathlen初始化为0
    if(T){
        if(T->lchild==NULL&&T->rchild==NULL){//如果该结点是叶子结点
            printf("叶子结点%2c到根结点的路径为：%2c", T->data, T->data);
            for(int i=pathlen-1; i>=0; i--)//输出二叉树中每个叶子结点到根节点的路径
                printf("%2c", path[i]);
            printf("\n");
        }
        else{//如果该结点不是叶子结点
            path[pathlen]=T->data;
            pathlen++;
            AllPath(T->lchild, path, pathlen);
            AllPath(T->rchild, path, pathlen);
            pathlen--;
        }
    }
}

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：");
    T=CreateBiTree(&T);
    printf("二叉树创建成功！\n");

    char path[100];
    printf("输出二叉树中每个叶子结点到根节点的路径:\n");
    AllPath(T, path, 0);
}

/*
    输出二叉树中每个叶子结点到根节点的路径
*/
