#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int key;
    char otherinfo[20];
}ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

/*�����������ĵݹ����*/
BSTree SearchBST(BSTree T, int key)
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
    if(!*T)                                                                //�ҵ�����λ�ã��ݹ����
    {
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                    //�����½��*S
        S->data=e;                                                        //�½�����������Ϊe
        S->lchild=NULL;                                                   //�½��*S��ΪҶ�ӽ��
        S->rchild=NULL;
        *T=S;                                                              //���½��*S���ӵ����ҵ��Ĳ���λ��
    }
    else if(e.key<(*T)->data.key)                                            //��*S����������
        InsertBST(&((*T)->lchild), e);
    else if(e.key>(*T)->data.key)                                            //��*S����������
        InsertBST(&((*T)->rchild), e);
}

/*�����������Ĵ���*/
void CreatBST(BSTree *T)
{
    *T=NULL;
    ElemType e;
    int i=1;
    printf("����������������ĵ�%d��Ԫ�أ��ؼ��֣���ע����",i);
    scanf("%d,%s",&e.key,&e.otherinfo);
    while(e.key!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("����������������ĵ�%d��Ԫ�أ��ؼ��֣���ע����",i);
        scanf("%d,%s",&e.key,&e.otherinfo);
    }
}

/*������������ɾ��*/
void DeleteBST(BSTree T, int key)
{
    BSTNode *p=T;
    BSTNode *f=NULL;
    while(p)
    {
        if(key==p->data.key)
            break;
        f=p;                                                            //*fΪ*p��˫�׽��
        if(key<p->data.key)
            p=p->lchild;
        else
            p=p->rchild;
    }
    if(!p) return;
    BSTNode *q=p;
    BSTNode *s;
    if((p->lchild)&&(p->rchild))                                        //��ɾ�����*p������������Ϊ��
    {
        s=p->lchild;
        while(s->rchild)                                                //��*p���������м���������ǰ����㣬�������½��
        {
            q=s;
            s=s->rchild;                                                //���ҵ���ͷ
        }
        p->data=s->data;                                                //sָ��ɾ�����ġ�ǰ����
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
        printf("%d ",T->data.key);
        InOrderTraverse(T->rchild);
    }
}

void main()
{
    BSTree BST;
    printf("������Ҫ�����Ķ�����������\n");
    CreatBST(&BST);
    printf("�����������������!\n");
    printf("�ö���������������������Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

    int key;
    BSTNode *SearchBST_Result;
    printf("���������ѯ��Ԫ�صĹؼ��֣�");
    scanf("%d",&key);
    SearchBST_Result=SearchBST(BST, key);
    printf("��ѯ�ɹ�����ѯ���Ϊ���ؼ��֣���ע��Ϣ����%d, %s",SearchBST_Result->data.key,SearchBST_Result->data.otherinfo);
    printf("\n");


    ElemType e;
    printf("������������Ԫ�أ��ؼ��֣���ע��Ϣ����");
    scanf("%d,%s",&e.key,&e.otherinfo);
    InsertBST(&BST, e);
    printf("����ɹ�������֮��Ķ���������Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

    printf("�������ɾ����Ԫ�صĹؼ��֣�");
    scanf("%d",&key);
    DeleteBST(BST, key);
    printf("ɾ���ɹ���ɾ��֮��Ķ���������Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

}

