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

int LeafNode(BiTree T){//ͳ�ƶ��������ĸ���
    if(T==NULL) return 0;
    else return LeafNode(T->lchild)+LeafNode(T->rchild)+1;
}

void main(){
    BiTree T;
    printf("�����򴴽�һ�ö�������\n");
    T=CreateBiTree(&T);
    printf("�����������ɹ���\n");
    printf("�ö��������ĸ���Ϊ��%d\n", LeafNode(T));
}

/*
    ͳ�ƶ��������ĸ���
*/
