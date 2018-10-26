#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//���򴴽�������
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

void PreOrderTraverse(BiTree T){//�������������
    if(T){
        printf("%2c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void ChangeLR(BiTree *T){//���������������Һ���
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
void ChangeLR(BiTree *T){//���������������Һ���
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
    printf("�����򴴽�һ�ö�������");
    T=CreateBiTree(&T);
    printf("�����������ɹ���\n");
    printf("�����ö����������Һ���...\n");
    ChangeLR(&T);
    printf("�����ɹ���\n");
    printf("����֮��ö�����Ϊ�������������");
    PreOrderTraverse(T);
}

/*
    ����������ÿ���������Һ��ӽ��
*/
