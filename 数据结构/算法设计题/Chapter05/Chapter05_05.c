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
int count;//��¼��������Ŀ��

void LevelNodeCount(BiTree T, int level){//�������������
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
    int levelCount[depth];//��¼������ÿ��Ŀ��
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
    printf("�����򴴽�һ�ö�������\n");
    T=CreateBiTree(&T);
    printf("�����������ɹ���\n");
    printf("�ö������Ŀ��Ϊ��%d", Width(T));
}

/*
    ���������������ȣ����������������ָ���������в��н����������ֵ����
*/
