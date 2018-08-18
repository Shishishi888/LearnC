#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct BiThrNode
{
    char data;
    struct BiThrNode *lchild, *rchild;
    int LTag, RTag;
}BiThrNode, *BiThrTree;

/*���������������������*/
BiThrTree CreateBiTree(BiThrTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiThrNode *)malloc(sizeof(BiThrNode));
        (*T)->data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

BiThrTree pre;

/*�Խ��PΪ������������������*/
void InThreading(BiThrTree p)
{
    if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->LTag=1;
            p->lchild=pre;
        }
        else
            p->LTag=0;
        if(!pre->rchild)
        {
            pre->RTag=1;
            pre->rchild=p;
        }
        else
            pre->RTag=0;
        pre=p;
        InThreading(p->rchild);
    }
}

/*��ͷ���Ķ���������������*/
BiThrTree InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt=(BiThrNode *)malloc(sizeof(BiThrNode));
    if(!(*Thrt)) exit(0);
    (*Thrt)->LTag=0;
    (*Thrt)->RTag=1;
    (*Thrt)->rchild=*Thrt;
    if(!T)
        (*Thrt)->lchild=*Thrt;
    else
    {
        (*Thrt)->lchild=T;
        pre=*Thrt;
        InThreading(T);
        pre->rchild=*Thrt;
        pre->RTag=1;
        (*Thrt)->rchild=pre;
    }
    return *Thrt;
}

/*������������������*/
void InOrderTraverse_Thr(BiThrTree T)                          //Tָ��ͷ��㣬ͷ�������lchildָ������
{
    BiThrTree p=T->lchild;                                     //pָ������
    while(p!=T)
    {
        while(p->LTag==0) p=p->lchild;                         //����������
        printf("%3c",p->data);                                 //����������Ϊ�յĽ��
        while(p->RTag==1&&p->rchild!=T)
        {
            p=p->rchild;                                       //�����������ʺ�̽��
            printf("%3c", p->data);
        }
        p=p->rchild;                                           //ת��p��������
    }
}

void main()
{
    BiThrTree T=NULL, Thrt=NULL;
    printf("***********************����һ�ö�������������б���***********************\n");
    printf("�����빹����������ַ����У�");
    T=CreateBiTree(&T);
    if(T)
    {
        printf("���������ʾ�Ķ���������ɹ���\n");
        printf("��������������������\n");
        Thrt=InOrderThreading(&Thrt, T);
        printf("���������������������");
        InOrderTraverse_Thr(Thrt);
    }
    else
    {
        printf("���������ʾ�Ķ��������첻�ɹ���\n");
    }
}

