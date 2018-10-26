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

int Depth(BiTree T){//��������������
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

void LongestPath(BiTree T){//������������·���Ľ���ֵ
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
    printf("�����򴴽�һ�ö�������");
    T=CreateBiTree(&T);
    printf("�����������ɹ���\n");

    printf("�ö��������·��Ϊ��");
    LongestPath(T);
}

/*
    ������������е�һ�����·�����ȣ��������·���ϸ�����ֵ
*/
