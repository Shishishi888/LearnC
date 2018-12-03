#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct{
    struct BSTNode *lchild;
    struct BSTNode *rchild;
    ElemType data;
    int balance;
}BBTNode, *BBTree;

BBTree CreateBBTree(BBTree *T){//����������������
    ElemType data;
    int balance;

    scanf("%d��%d ", &data, &balance);//���룺data��balance+�ո�
    if(data==-1)
        *T=NULL;
    else{
        *T=(BBTNode *)malloc(sizeof(BBTNode));
        if(!(*T)) exit(0);
        (*T)->lchild=CreateBBTree(&((*T)->lchild));
        (*T)->rchild=CreateBBTree(&((*T)->rchild));
        (*T)->data=data;
        (*T)->balance=balance;
    }
    return *T;
}

/*
    ������Ĳ��Ϊ1��ѭ������ƽ���������ÿ����һ�㣬�߶ȼ�1��ֱ������������
    ����������Ҷ�ӽ�㣬���ø߶�ֵ����ƽ��������ĸ߶ȡ�����ԭ��Ϊ������ƽ
    ������Ϊ0ʱ����ѡ����һ��֧���±�������ƽ�����Ӳ�Ϊ0����ƽ�����ӵ���1ʱ��
    ���֧���±�����ƽ�����ӵ���-1ʱ���ҷ�֧���±�����
*/

int Height(BBTree T){//����ƽ�����Ӽ���ƽ������������
    int count=0;//��¼ƽ������������
    BBTNode *p=T;

    while(p){
        count++;
        if(p->balance>0)//��������ȴ���������
            p=p->lchild;
        else
            p=p->rchild;//���������С�ڵ���������
    }

    return count;
}

void main(){
    printf("���ȴ���һ��ƽ������������������ʽ��data��balance+�ո�-1��ʾ�ս�㣩��\n");
    BBTree BBT;

    CreateBBTree(&BBT);
    printf("�����ɹ���\n");
    printf("��ƽ��������ĸ߶�Ϊ��%d", Height(BBT));
}

/*
    ����һ��ƽ���������ÿ����㶼������ƽ������b�������һ���㷨����ƽ��������ĸ߶�
*/
