#include <stdio.h>
#include <malloc.h>

typedef struct{
    struct BSTNode *llink;
    struct BSTNode *rlink;
    int data;
    int count;
}BSTNode, *BSTree;

void InsertBST(BSTree *T, int e){//���½��������������
    if(!*T){                                                               //�ҵ�����λ�ã��ݹ����{
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                     //�����½��*S
        S->llink=NULL;                                                     //�½��*S��ΪҶ�ӽ��
        S->data=e;                                                         //�½�����������Ϊe
        S->count=0;
        S->rlink=NULL;
        *T=S;                                                     //���½��*S���ӵ����ҵ��Ĳ���λ��
    }
    else if(e<(*T)->data)                                         //��*S����������
        InsertBST(&((*T)->llink), e);
    else if(e>(*T)->data)                                         //��*S����������
        InsertBST(&((*T)->rlink), e);
}


void CreatBST(BSTree *T){//��������������
    *T=NULL;
    int e;
    int i=1;
    printf("����������������ĵ�%d��Ԫ�أ�",i);
    scanf("%d",&e);
    while(e!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("����������������ĵ�%d��Ԫ�أ�",i);
        scanf("%d",&e);
    }
}


void InOrderTraverse(BSTree T){//�����������������
    if(T){
        InOrderTraverse(T->llink);
        printf("%d��%d  ",T->data, T->count);
        InOrderTraverse(T->rlink);
    }
}

int Search_Insert_BST(BSTree T, int data){//���һ������
    if(!T) exit(0);
    BSTNode *p=T;//����ָ��p��ʼ��Ϊ�����������ĸ����
    BSTNode *q=NULL;

    while(p&&data!=p->data){//���ҽ��
        if(data<p->data){
            q=p;
            p=p->llink;
        }
        else if(data>p->data){
            q=p;
            p=p->rlink;
        }
    }

    if(p){//���ҵ��ý��
        (p->count)++;
        return 1;
        }

    else{//�ý�㲻����
        p=(BSTNode *)malloc(sizeof(BSTNode));
        p->llink=NULL;
        p->rlink=NULL;
        p->data=data;
        p->count=0;

        if(data<q->data)
            q->llink=p;
        else if(data>q->data)
            q->rlink=p;

        return 0;
    }
}

/*
int Search_Insert_BST(BSTree T, int X){
    BSTNode *s=(BSTNode *)malloc(sizeof(BSTNode));
    s->data=X;
    s->count=0;
    s->llink=s->rlink=NULL;

    if(!T){
        T=s;
        return 0;
    }

    BSTNode *f=NULL;
    BSTNode *q=T;

    while(q){
        if(q->data==X){
            q->count++;
            return 1;
        }

        f=q;

        if(X<q->data)
            q=q->llink;
        else
            q=q->rlink;
    }

    if(f->data>X)
        f->llink=s;
    else
        f->rlink=s;

    return 0;
}
*/

void main(){
    printf("���ȴ���һ�ö�����������\n");
    BSTree BST;
    CreatBST(&BST);
    printf("�����ɹ���\n");
    printf("�ö�����������������������data��count��Ϊ��");
    InOrderTraverse(BST);
    printf("\n");

    int data;
    printf("����������Ҫ���ҽ���ֵ��");
    scanf("%d", &data);
    int result=Search_Insert_BST(BST, data);
    printf("���ҳɹ���\n");
    if(result)
        printf("������Ҫ���ҵĽ�㣡\n");
    else{
        printf("��������Ҫ���ҵĽ�㣡\n");
        printf("���ڽ��ý����뵽������������ ...\n");
        printf("����ɹ���\n");
    }

    printf("�ö�����������������������data��count��Ϊ��");
    InOrderTraverse(BST);
}

/*
    ��֪������T�Ľ����ʽΪ(llink, data, count, rlink)�������в���ֵΪX�Ľ�㣬
    ���ҵ����������count����1��������Ϊһ���½��������У��������Ϊ������
    ������д����ǵݹ��㷨��
*/
