#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX 20
#define OK 1
#define ERROR 0

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*���������˳����������*/
BiTree CreateBiTree(BiTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!(*T)) exit(0);
        (*T)->data=ch;
        (*T)->lchild=CreateBiTree(&((*T)->lchild));
        (*T)->rchild=CreateBiTree(&((*T)->rchild));
    }
    return *T;
}

/*��α������*/
void LevelOrder(BiTree T)
{
    BiTree Queue[MAX], b;
    int front, rear;
    front=rear=0;
    if(T)
    {
        Queue[rear++]=T;
        while(front!=rear)
        {
            b=Queue[front++];
            printf("%2c",b->data);
            if(b->lchild!=NULL) Queue[rear++]=b->lchild;
            if(b->rchild!=NULL) Queue[rear++]=b->rchild;
        }
    }
}

/*�������������*/
void PreOrderTraverse(BiTree T)
{
    if(T)
    {
        printf("%2c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

/*�������������*/
void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%2c",T->data);
        InOrderTraverse(T->rchild);
    }
}

/*�������������*/
void PostOrderTraverse(BiTree T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%2c",T->data);
    }
}
/*���ƶ�����*/
void Copy(BiTree T, BiTree *NewT)
{
    if(T==NULL)
    {
        *NewT=NULL;
        return;
    }
    else
    {
        *NewT=(BiTNode *)malloc(sizeof(BiTNode));
        (*NewT)->data=T->data;
        Copy(T->lchild, &((*NewT)->lchild));
        Copy(T->rchild, &((*NewT)->rchild));
    }
}

/*��������������*/
int Depth(BiTree T)
{
    if(T==NULL)
        return 0;
    else
    {
        int m=Depth(T->lchild);
        int n=Depth(T->rchild);
        if(m>n)
            return m+1;
        else
            return n+1;
    }
}

/*ͳ�ƶ������н��ĸ���*/
int NodeCount(BiTree T)
{
    if(T==NULL)
        return 0;
    else
        return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
}

/*ͳ�ƶ�������Ҷ�ӽ��ĸ���*/
int LeafCount(BiTree T)
{
    if(T==NULL)
        return 0;
    else if(T->lchild==NULL&&T->rchild==NULL)
        return 1;
    else
        return LeafCount(T->lchild)+LeafCount(T->rchild);
}

/*������*/
void main()
{
    BiTree T=NULL;
    printf("*******************���õݹ麯�������һ�ö�����*******************\n");
    printf("�����빹����������ַ����У�");
    if(T=CreateBiTree(&T))
    {
        printf("�����������ɹ���\n");
        printf("����������������:\n");
        LevelOrder(T);
        printf("\n");

        printf("����������������:\n");
        PreOrderTraverse(T);
        printf("\n");

        printf("����������������:\n");
        InOrderTraverse(T);
        printf("\n");

        printf("����������������:\n");
        PostOrderTraverse(T);
        printf("\n");

        printf("���Ƹö�����\n");
        BiTree NewT;
        Copy(T, &NewT);
        printf("���Ƴɹ������ƽ��Ϊ���������������ƶ���������\n");
        PreOrderTraverse(NewT);
        printf("\n");

        printf("�ö����������Ϊ��");
        printf("%d\n",Depth(T));

        printf("�ö������Ľ�����Ϊ��");
        printf("%d\n",NodeCount(T));

        printf("�ö�������Ҷ�ӽ�����Ϊ��");
        printf("%d\n",LeafCount(T));

    }
    else
        printf("���ź������ܳɹ�����������������\n");
}
