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

void AllPath(BiTree T, char path[], int pathlen){//�����������ÿ��Ҷ�ӽ�㵽���ڵ��·����pathlen��ʼ��Ϊ0
    if(T){
        if(T->lchild==NULL&&T->rchild==NULL){//����ý����Ҷ�ӽ��
            printf("Ҷ�ӽ��%2c��������·��Ϊ��%2c", T->data, T->data);
            for(int i=pathlen-1; i>=0; i--)//�����������ÿ��Ҷ�ӽ�㵽���ڵ��·��
                printf("%2c", path[i]);
            printf("\n");
        }
        else{//����ý�㲻��Ҷ�ӽ��
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
    printf("�����򴴽�һ�ö�������");
    T=CreateBiTree(&T);
    printf("�����������ɹ���\n");

    char path[100];
    printf("�����������ÿ��Ҷ�ӽ�㵽���ڵ��·��:\n");
    AllPath(T, path, 0);
}

/*
    �����������ÿ��Ҷ�ӽ�㵽���ڵ��·��
*/
