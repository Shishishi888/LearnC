#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree CreateBiTree(BiTree *T){//����������������
    int data;
    scanf(" %d",&data);//���룺�ո�+data
    if(data==-1)
        *T=NULL;
    else{
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->data=data;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

/*
    ���ݶ����������Ķ��壬�Զ��������еݹ�������������Ĺؼ��ֱȸ����Ĺؼ���С��
    �������Ĺؼ��ֱȸ����Ĺؼ��ִ�һ���в�������������ж����Ƕ�����������
    ͨ������flag��ֵ���жϣ�flagΪ1��ʾ�Ƕ�����������Ϊ0��ʾΪ�Ƕ�����������flag
    ��ֵΪ1.��ȫ��ָ�����pre������ָ��������̽���ǰ����
    ��1�����ȵݹ������������
    ��2�����preΪNULL����ʹ��ָ�����㣬���򣬽���ǰ�����pre��ָ��ǰ�������
         �Ƚϣ����ǰ������ֵС�ڵ�ǰ����ֵ������preָ��ǰ��㣻���ǰ����
         ���ֵ���ڵ�ǰ����ֵ�����ʾ���Ƕ�����������flag��Ϊ0��
    ��3�����ݹ������������
*/
int flag=1;//�����������ı�־����ʼ��Ϊ1
BiTNode *pre=NULL;//ָ��ǰ�����

int JudgeBST(BiTree T, int *flag){//�ж��Ƿ�Ϊ����������
    if(T&&(*flag)){
        JudgeBST(T->lchild, flag);
        if(pre==NULL)
            pre=T;
        else{
            if(pre->data<T->data) pre=T;
            else *flag=0;
        }
        JudgeBST(T->rchild, flag);
    }
}

void main(){
    printf("���ȴ���һ�ö�������\n");
    BiTree T;
    T=CreateBiTree(&T);
    printf("�����������ɹ�!\n");
    JudgeBST(T, &flag);
    if(flag)
        printf("�ö������Ƕ�����������");
    else
        printf("�ö��������Ƕ�����������");
}

/*
    ��дһ���б�����������Ƿ�Ϊ�������������㷨
*/
