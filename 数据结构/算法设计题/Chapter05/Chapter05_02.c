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

/*
int CmpTree(BiTree T1, BiTree T2){//判断两棵二叉树是否相等
    if(T1==NULL&&T2==NULL)
        return 1;
    else if((T1!=NULL&&T2==NULL)||(T1==NULL&&T2!=NULL))
        return 0;
    else{
        if(T1->data!=T2->data)
            return 0;
        else{
            int left, right;
            left=CmpTree(T1->lchild, T2->lchild);
            right=CmpTree(T1->rchild, T2->rchild);
            return left&&right;}
        }
}
*/

int CmpTree(BiTree T1, BiTree T2){//判断两棵二叉树是否相等
    if(T1==NULL&&T2==NULL)//T1，T2均为NULL
        return 1;
    else if(T1==NULL||T2==NULL)//T1，T2其中一个为NULL
        return 0;
    if(T1->data!=T2->data)//T1，T2均不为NULL，但是T1，T2的值不相等
        return 0;

    //T1，T2均不为NULL，并且T1，T2的值相等
    int left, right;
    left=CmpTree(T1->lchild, T2->lchild);
    right=CmpTree(T1->rchild, T2->rchild);
    return left&&right;
}

void main(){
    BiTree T1;
    printf("请先序创建第一棵二叉树：\n");
    T1=CreateBiTree(&T1);
    printf("第一棵二叉树创建成功！\n");
    BiTree T2;
    printf("请先序创建第二棵二叉树：\n");
    T2=CreateBiTree(&T2);//bug：当建立第二棵二叉树时，最后需要多输入一个‘#’；
                         //当建立两棵相同的二叉树时，两棵二叉树的遍历结果相同，但是第二棵二叉树会比第一棵二叉树多出一个结点
    printf("第二棵二叉树创建成功！\n");

    if(CmpTree(T1, T2))
        printf("您创建的两棵二叉树相等！");
    else
        printf("您创建的两棵二叉树不相等！");
}

/*
    判别两棵树是否相等
*/
