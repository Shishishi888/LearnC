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
{//pre��ȫ�ֱ�������ʼ��ʱ���Һ���ָ��Ϊ�գ���������������㿪ʼ������
    if(p)
    {
        InThreading(p->lchild);//�������ݹ�������
        if(!p->lchild)//���p������Ϊ��
        {
            p->LTag=1;//��p����������
            p->lchild=pre;//p������ָ��ָ��pre��ǰ����
        }
        else
            p->LTag=0;
        if(!pre->rchild)//���pre���Һ���Ϊ��
        {
            pre->RTag=1;//��pre����������
            pre->rchild=p;//pre���Һ���ָ��ָ��p����̣�
        }
        else
            pre->RTag=0;
        pre=p;//����preָ��p��ǰ��
        InThreading(p->rchild);//�������ݹ�������
    }
}

/*��ͷ���Ķ���������������*/
BiThrTree InOrderThreading(BiThrTree *Thrt, BiThrTree T)//�������������T��������������������Thrtָ��ͷ���
{
    *Thrt=(BiThrNode *)malloc(sizeof(BiThrNode));//����ͷ���
    (*Thrt)->LTag=0;//ͷ��������ӣ������ǿգ���������Ϊ����
    (*Thrt)->RTag=1;//ͷ�����Һ���ָ��Ϊ������
    (*Thrt)->rchild=*Thrt;//��ʼ��ʱ��ָ��ָ���Լ�
    if(!T)//����Ϊ�գ�����ָ��Ҳָ���Լ�
        (*Thrt)->lchild=*Thrt;
    else
    {
        (*Thrt)->lchild=T;//ͷ��������ָ������
        pre=*Thrt;//pre��ֵָ��ͷ���
        InThreading(T);//���������������㷨������TΪ���Ķ�������������������
        pre->rchild=*Thrt;//�����������㷨������preΪ���ҽ�㣬pre��������ָ��ͷ���
        pre->RTag=1;
        (*Thrt)->rchild=pre;//ͷ����������ָ��pre
    }
    return *Thrt;
}

/*������������������*/
void InOrderTraverse_Thr(BiThrTree T)                          //Tָ��ͷ��㣬ͷ��������lchildָ������
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

