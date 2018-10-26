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

/*
int CmpTree(BiTree T1, BiTree T2){//�ж����ö������Ƿ����
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

int CmpTree(BiTree T1, BiTree T2){//�ж����ö������Ƿ����
    if(T1==NULL&&T2==NULL)//T1��T2��ΪNULL
        return 1;
    else if(T1==NULL||T2==NULL)//T1��T2����һ��ΪNULL
        return 0;
    if(T1->data!=T2->data)//T1��T2����ΪNULL������T1��T2��ֵ�����
        return 0;

    //T1��T2����ΪNULL������T1��T2��ֵ���
    int left, right;
    left=CmpTree(T1->lchild, T2->lchild);
    right=CmpTree(T1->rchild, T2->rchild);
    return left&&right;
}

void main(){
    BiTree T1;
    printf("�����򴴽���һ�ö�������\n");
    T1=CreateBiTree(&T1);
    printf("��һ�ö����������ɹ���\n");
    BiTree T2;
    printf("�����򴴽��ڶ��ö�������\n");
    T2=CreateBiTree(&T2);//bug���������ڶ��ö�����ʱ�������Ҫ������һ����#����
                         //������������ͬ�Ķ�����ʱ�����ö������ı��������ͬ�����ǵڶ��ö�������ȵ�һ�ö��������һ�����
    printf("�ڶ��ö����������ɹ���\n");

    if(CmpTree(T1, T2))
        printf("�����������ö�������ȣ�");
    else
        printf("�����������ö���������ȣ�");
}

/*
    �б��������Ƿ����
*/
