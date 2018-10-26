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
int count;//记录二叉树层的宽度

void LevelNodeCount(BiTree T, int level){//按层遍历二叉树
    if(T==NULL||level<1)
        return;
    else if(level==1)
        count++;
    else{
        LevelNodeCount(T->lchild, level-1);
        LevelNodeCount(T->rchild, level-1);
    }
}

int Width(BiTree T){
    int depth=Depth(T);
    int levelCount[depth];//记录二叉树每层的宽度
    for(int i=0; i<depth; i++){
        LevelNodeCount(T, i);
        levelCount[i]=count;
        count=0;
    }

    int maxWidth=0;
    for(int i=0; i<depth; i++){
        if(maxWidth<levelCount[i])
            maxWidth=levelCount[i];
    }

    return maxWidth;
}

void main(){
    BiTree T;
    printf("请先序创建一棵二叉树：\n");
    T=CreateBiTree(&T);
    printf("二叉树创建成功！\n");
    printf("该二叉树的宽度为：%d", Width(T));
}

/*
    计算二叉树的最大宽度（二叉树的最大宽度是指二叉树所有层中结点个数的最大值）。
*/
