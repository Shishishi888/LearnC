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

void DoubleTraverse(BiTree T){//˫�����������
    if(T){
        printf("%2c", T->data);
        DoubleTraverse(T->lchild);
        printf("%2c", T->data);
        DoubleTraverse(T->rchild);
    }
}

void main(){
    BiTree T;
    printf("�����򴴽�һ�ö�������");
    CreateBiTree(&T);
    printf("�����������ɹ���\n");
    printf("˫������ö����������Ϊ��");
    DoubleTraverse(T);
}

/*
    ��ƶ�������˫������㷨��˫�������ָ���ڶ�������ÿһ�������˵���ȷ��������㣬
    �ٰ�˫�����������������Ȼ����һ�η��������㣬��������˫�������������������
*/
