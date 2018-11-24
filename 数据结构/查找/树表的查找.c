#include <stdio.h>
#include <malloc.h>

typedef int KeyType;
typedef char InfoType[20];

typedef struct
{
    KeyType key;
    InfoType otherinfo;
}ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

/*�����������ķǵݹ����*/
BSTree SearchBST(BSTree T, KeyType key)
{
    BSTNode *p=T;
    while(p)
    {
        if(key==p->data.key)
            break;
        else if(key<p->data.key)
            p=p->lchild;
        else
            p=p->rchild;
    }

    return p;
}

/*�����������ĵݹ����*/
BSTree SearchBST_Re(BSTree T, KeyType key)
{
    if((!T)||key==T->data.key)
        return T;
    else if(key<T->data.key)
        return SearchBST(T->lchild, key);
    else
        return SearchBST(T->rchild, key);
}

/*�����������Ĳ���*/
void InsertBST(BSTree *T, ElemType e)
{
    if(!*T)                                                               //�ҵ�����λ�ã��ݹ����
    {
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                    //�����½��*S
        S->data=e;                                                        //�½�����������Ϊe
        S->lchild=NULL;                                                   //�½��*S��ΪҶ�ӽ��
        S->rchild=NULL;
        *T=S;                                                             //���½��*S���ӵ����ҵ��Ĳ���λ��
    }
    else if(e.key<(*T)->data.key)                                         //��*S����������
        InsertBST(&((*T)->lchild), e);
    else if(e.key>(*T)->data.key)                                         //��*S����������
        InsertBST(&((*T)->rchild), e);
}

/*�����������Ĵ���*/
void CreatBST(BSTree *T)
{
    *T=NULL;
    ElemType e;
    int i=1;
    printf("����������������ĵ�%d��Ԫ�أ��ؼ��֣���Ϣ����",i);
    scanf("%d��%s",&e.key,&e.otherinfo);
    while(e.key!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("����������������ĵ�%d��Ԫ�أ��ؼ��֣���Ϣ����",i);
        scanf("%d��%s",&e.key,&e.otherinfo);
    }
}

/*������������ɾ��*/
void DeleteBST(BSTree T, KeyType key)
{
    BSTNode *p=T;
    BSTNode *f=NULL;

    while(p)                                                             //Ѱ�Ҵ�ɾ���*p
    {
        if(key==p->data.key)
            break;
        f=p;                                                             //*fΪ*p�ĸ��׽��
        if(key<p->data.key)
            p=p->lchild;
        else
            p=p->rchild;
    }

    if(!p) return;
    BSTNode *q=p;
    BSTNode *s;

    if((p->lchild)&&(p->rchild))                                        //��ɾ���*p��������������Ϊ��
    {
        s=p->lchild;                                                    //��*p���������в�����ǰ����㣬�������½��
        while(s->rchild)                                                //*sָ��*p��ǰ�����
        {
            q=s;                                                        //*qָ��*s�ĸ��׽��
            s=s->rchild;
        }
        p->data=s->data;
        if(q!=p)
            q->rchild=s->lchild;                                        //�ؽ�*q��������
        else
            q->lchild=s->lchild;                                        //�ؽ�*q��������
        free(s);
        return;
    }
    else if(!p->rchild)                                                 //��ɾ�����*p����������ֻ��Ҫ�ؽ���������
        p=p->lchild;
    else if(!p->lchild)                                                 //��ɾ�����*p����������ֻ��Ҫ�ؽ���������
        p=p->rchild;

    if(!f)                                                              //��ɾ�����Ϊ�����
        T=p;
    else if(q==f->lchild)                                               //�ҵ�*f��������λ��
        f->lchild=p;
    else                                                                //�ҵ�*f��������λ��
        f->rchild=p;
    free(q);
}

/*�������������������*/
void InOrderTraverse(BSTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d��%s  ",T->data.key, T->data.otherinfo);
        InOrderTraverse(T->rchild);
    }
}

void main()
{
    BSTree BST;
    printf("�����ȴ���һ�ö�����������\n");
    CreatBST(&BST);
    printf("�����������������!\n");
    printf("�ö���������������������Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

    KeyType key;
    BSTNode *SearchBST_Result;
    printf("���������ѯ��Ԫ�صĹؼ��֣�");
    scanf("%d",&key);
    SearchBST_Result=SearchBST(BST, key);
    printf("��ѯ�ɹ����ǵݹ��ѯ������ؼ��֣���Ϣ��Ϊ��%d, %s",SearchBST_Result->data.key,SearchBST_Result->data.otherinfo);
    printf("\n");
    SearchBST_Result=SearchBST_Re(BST, key);
    printf("��ѯ�ɹ��� �ݹ��ѯ������ؼ��֣���Ϣ��Ϊ��%d, %s",SearchBST_Result->data.key,SearchBST_Result->data.otherinfo);
    printf("\n");

    ElemType e;
    printf("������������Ԫ�أ��ؼ��֣���Ϣ����");
    scanf("%d��%s",&e.key, &e.otherinfo);
    InsertBST(&BST, e);
    printf("����ɹ�������֮��Ķ������������ؼ��֣���Ϣ��Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

    printf("�������ɾ����Ԫ�صĹؼ��֣�");
    scanf("%d", &key);
    DeleteBST(BST, key);
    printf("ɾ���ɹ���ɾ��֮��Ķ������������ؼ��֣���Ϣ��Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

}

